#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define W 1000
#define H 800
#define MS 0.1
#define RS 0.1
#define TEX_SIZE 64

typedef struct s_colors
{
    char *c;
    char *f;
    int ceil[3];
    int floor[3];
}   t_colors;

typedef struct s_directions
{
    char *north;
    char *south;
    char *east;
    char *west;
}   t_directions;

typedef struct s_vars
{
    char **map;
    char facing_dir;
    double xp_pos;
    double yp_pos;
}   t_vars;
typedef struct s_parsing
{
    char **file;
    int first_ceil;
    int last_ceil;
    int ceil_line;
    char *ceil;
    int first_floor;
    int last_floor;
    int floor_line;
    char *floor;
} t_parsing;

typedef struct s_texture
{
    void *img;
    char *addr;
    int bpp, line_len, endian;
} t_texture;

typedef struct s_game
{
    void *mlx, *win, *frame_img;
    char *frame_addr;
    int frame_bpp, frame_line, frame_endian;
    t_vars vars;
    t_colors colors;
    t_directions dirs;
    t_texture tex[4]; // 0=north, 1=south, 2=east, 3=west
    double dx, dy, planx, plany;
    int map_w, map_h;
} t_game;

// Sample map with player starting position
char *sample_map[] = {
    "1111111111111111111",
    "100000000001111111",
    "1001000000000111111", 
    "10000000000001",
    "1 000001", // Player facing North
    "10111001",
    "1N1 100001",
    "111 1111",
    NULL
};

void put_pixel(t_game *g, int x, int y, int color) {
    *(int*)(g->frame_addr + y*g->frame_line + x*(g->frame_bpp/8)) = color;
}

int get_texture_pixel(t_texture *tex, int x, int y) {
    if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE) return 0;
    return *(int*)(tex->addr + y*tex->line_len + x*(tex->bpp/8));
}

int get_map_cell(t_game *g, int x, int y) {
    if (x < 0 || x >= g->map_w || y < 0 || y >= g->map_h) return 1;
    if (g->vars.map[y][x] == '1') return 1;
    return 0;
}

void set_player_direction(t_game *g, char dir) 
{
    if (dir == 'N') 
    {
        g->dx = 0; g->dy = -1; 
        g->planx = 0.66;
        g->plany = 0;
    } 
    else if (dir == 'S') 
    {
        g->dx = 0; g->dy = 1; 
        g->planx = -0.66;
        g->plany = 0;
    }
    else if (dir == 'E')
    {
        g->dx = 1;
        g->dy = 0;
        g->planx = 0; 
        g->plany = 0.66;
    } 
    else if (dir == 'W')
    {
        g->dx = -1;
        g->dy = 0;
        g->planx = 0;
        g->plany = -0.66;
    }
}

void init_map(t_game *g) 
{
    g->map_h = 0;
    while (sample_map[g->map_h]) g->map_h++;
    
    // Find the maximum width across all rows
    g->map_w = 0;
    int i = 0;
    while (i < g->map_h) {
        int len = strlen(sample_map[i]);
        if (len > g->map_w) 
            g->map_w = len;
        i++;
    }
    
    g->vars.map = malloc(g->map_h * sizeof(char*));
    int y = 0;
    while (y < g->map_h)
    {
        g->vars.map[y] = malloc(g->map_w + 1);
        
        // Copy the row and pad with '1' if necessary
        strcpy(g->vars.map[y], sample_map[y]);
        int current_len = strlen(sample_map[y]);
        while (current_len < g->map_w)
        {
            g->vars.map[y][current_len] = '1';
            current_len++;
        }
        g->vars.map[y][g->map_w] = '\0';
    
        int x = 0;
        while (x < g->map_w) {
            char c = g->vars.map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                g->vars.xp_pos = x + 0.5;//x + 0.5;
                g->vars.yp_pos = y + 0.5;//y + 0.5;
                g->vars.facing_dir = c;
                set_player_direction(g, c);
                g->vars.map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
}

int load_texture(t_game *g, int id, char *path)
{
    t_texture *tex = &g->tex[id];
    tex->img = mlx_xpm_file_to_image(g->mlx, path, &tex->line_len, &tex->endian);
    if (!tex->img) return 0;
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    return 1;
}

void init_textures(t_game *g)
{
    // Set default texture paths
    g->dirs.north = "./textures/eagle.xpm";
    g->dirs.south = "./textures/mossy.xpm";  
    g->dirs.east = "./textures/greystone.xpm";
    g->dirs.west = "./textures/wood.xpm";
    
    // Try to load textures, use solid colors if files don't exist
    load_texture(g, 0, g->dirs.north);
    load_texture(g, 1, g->dirs.south);
    load_texture(g, 2, g->dirs.east);
    load_texture(g, 3, g->dirs.west);
} int screen_x = 600;

void init_colors(t_game *g) 
{
    g->colors.ceil[0] = 135; // Sky blue
    g->colors.ceil[1] = 206;
    g->colors.ceil[2] = 235;
    
    g->colors.floor[0] = 68; // Dark gray
    g->colors.floor[1] = 68;
    g->colors.floor[2] = 68;
}

int get_ceiling_color(t_game *g)
{
    return (g->colors.ceil[0] << 16) | (g->colors.ceil[1] << 8) | g->colors.ceil[2];
}

int get_floor_color(t_game *g)
{
    return (g->colors.floor[0] << 16) | (g->colors.floor[1] << 8) | g->colors.floor[2];
}

void cast_ray(t_game *g, int screen_x) 
{
    double camera_x = 2 * screen_x / (double)W - 1;
    double ray_dx = g->dx + g->planx * camera_x;
    double ray_dy = g->dy + g->plany * camera_x;
    
    int map_x = (int)g->vars.xp_pos, map_y = (int)g->vars.yp_pos;
    double delta_x = fabs(1/ray_dx), delta_y = fabs(1/ray_dy);// what is the number i want to use to increment the value of interceptions 
    double side_x, side_y;// first horizontal and vertical intersection
    int step_x, step_y;
    
    if (ray_dx < 0) //left 
    {
        step_x = -1;
        side_x = (g->vars.xp_pos - map_x) * delta_x;
    } 
    else //right
    {
        step_x = 1;
        side_x = (map_x + 1 - g->vars.xp_pos) * delta_x;
    }
    
    if (ray_dy < 0) // up
    {
        step_y = -1;
        side_y = (g->vars.yp_pos - map_y) * delta_y;
    }
    else //down
    {
        step_y = 1;
        side_y = (map_y + 1 - g->vars.yp_pos) * delta_y;
    }
    
    int hit = 0, side = 0;
    // if hit y side the side set to 1  &and&   if hit x side the side set to 0
    while (!hit) 
    {
        if (side_x < side_y) 
        {
            side_x += delta_x;
            map_x += step_x;
            side = 0;
        } 
        else
        {
            side_y += delta_y;
            map_y += step_y;
            side = 1;
        }
        if (get_map_cell(g, map_x, map_y))
            hit = 1;
    }
    
    double perp_dist;
    if (side == 0)
        perp_dist = (map_x - g->vars.xp_pos + (1 - step_x) / 2) / ray_dx;
    else
        perp_dist = (map_y - g->vars.yp_pos + (1 - step_y) / 2) / ray_dy;
    
    int line_height = (int)(H / perp_dist);
    int start = -line_height / 2 + H / 2;
    int end = line_height / 2 + H / 2;
    
    // clamping
    if (start < 0)
        start = 0;
    if (end >= H)
        end = H - 1;
    
    // Determine texture based on wall face
    int tex_id = 0;
    if (side == 0)
        tex_id = ray_dx > 0 ? 3 : 2; // West or East
    else
        tex_id = ray_dy > 0 ? 0 : 1; // North or South
    
    // Calculate texture coordinates
    double wall_x;
    if (side == 0)
    {
        wall_x = g->vars.yp_pos + perp_dist * ray_dy;
    } 
    else 
    {
        wall_x = g->vars.xp_pos + perp_dist * ray_dx;
    }
    wall_x -= floor(wall_x);
    
    int tex_x = (int)(wall_x * TEX_SIZE);
    if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
        tex_x = TEX_SIZE - tex_x - 1;
    
    double step = 1.0 * TEX_SIZE / line_height;
    double tex_pos = (start - H / 2 + line_height / 2) * step;
    
    // Draw ceiling
    int y = 0;
    while (y < start)
    {
        put_pixel(g, screen_x, y, get_ceiling_color(g));
        y++;
    }
    
    // Draw wall with texture
    while (y < end)
    {
        int tex_y = (int)tex_pos & (TEX_SIZE - 1);
        tex_pos += step;
        int color = get_texture_pixel(&g->tex[tex_id], tex_x, tex_y);
        if (!color) 
            color = side == 1 ? 0x404040 : 0x808080; // Fallback colors
        put_pixel(g, screen_x, y, color);
        y++;
    }
    
    // Draw floor
    while (y < H) 
    {
        put_pixel(g, screen_x, y, get_floor_color(g));
        y++;
    }
}

int render(t_game *g)
{
    int x = 0;
    while (x < W) 
    {
        cast_ray(g, x);
        x++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->frame_img, 0, 0);
    return 0;
}

void move_player(t_game *g, double move_x, double move_y) 
{
    double new_x = g->vars.xp_pos + move_x;
    double new_y = g->vars.yp_pos + move_y;

    if (!get_map_cell(g, (int)new_x, (int)g->vars.yp_pos))
         g->vars.xp_pos = new_x;
    if (!get_map_cell(g, (int)g->vars.xp_pos, (int)new_y))
        g->vars.yp_pos = new_y;
}

void rotate_player(t_game *g, double angle)
{
    double old_dx = g->dx;
    double old_px = g->planx;

    g->dx = g->dx * cos(angle) - g->dy * sin(angle);
    g->dy = old_dx * sin(angle) + g->dy * cos(angle);
    g->planx = g->planx * cos(angle) - g->plany * sin(angle);
    g->plany = old_px * sin(angle) + g->plany * cos(angle);
}

int key_press(int key, t_game *g) 
{
    if (key == 65307)
        exit(0);
    if (key == 'w')
        move_player(g, g->dx * MS, g->dy * MS);
    if (key == 's')
        move_player(g, -g->dx * MS, -g->dy * MS);
    if (key == 'a')
        move_player(g, g->dy * MS, -g->dx * MS);
    if (key == 'd')
        move_player(g, -g->dy * MS, g->dx * MS);
    if (key == 65361)
        rotate_player(g, -RS);
    if (key == 65363)
        rotate_player(g, RS);
    return 0;
}

int main() {
    t_game g = {0};
    
    g.mlx = mlx_init();
    g.win = mlx_new_window(g.mlx, W, H, "Raycaster with Structs");
    g.frame_img = mlx_new_image(g.mlx, W, H);
    g.frame_addr = mlx_get_data_addr(g.frame_img, &g.frame_bpp, &g.frame_line, &g.frame_endian);
    
    init_map(&g);
    init_textures(&g);
    init_colors(&g);
    
    mlx_hook(g.win, 2, 1L<<0, key_press, &g);
    mlx_loop_hook(g.mlx, render, &g);
    mlx_loop(g.mlx);
    return 0;
}