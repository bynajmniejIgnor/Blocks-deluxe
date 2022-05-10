# Blocks deluxe (projekt zaliczeniowy z programowania niskopoziomowego)

Autorzy:

- Adam Piaseczny - 151757

- Igor Szczepaniak - 151918

Gra podobna do tetrisa, gdzie celem gry jest ciągłe uzupełnianie rzędów spadającymi klockami. Jest ona napisana w **C** i działa na **Windows** jak i na **Linux** (Fedora 35). Gra używa `SDL2` jako silnika graficznego.

![Brak opisu.](https://qph.fs.quoracdn.net/main-qimg-356e2b21c801381db2890dab49a9ea88)

### Jak grać?

- `ESC`

  - Wychodzenie z programu

- `Lewa strzałka`

  - Przesunięcie klocka w lewo

- `Prawa strzałka`

  - Przesunięcie klocka w prawo

- `Strzałka w góre`

  - Obrócenie klocka

- `Strzałka w dół`

  - Opuszczenie klocka o jedną linię

- `Spacja` (dla odważnych)

  - Domyślnie co 5 wyczyszczonych linii gra przyspiesza tempo spadania klocków

  - Naciśnięcie `Spacji` powoduje dwukrotne przyspieszenie tempa gry

### Funkcje zawarte w projekcie

```
main.c (główna funkcjonalność)
clear_block      function    void clear_block(){
gravity          function    void gravity(SDL_Renderer* renderer, SDL_Window* window){
main             function    int main(int argc, char* args[]){
rotate           function    void rotate(){
spawn_random_tetronimo function   void spawn_random_tetronimo(SDL_Renderer* renderer, SDL_Window* window){
time_gravity     function    void time_gravity(SDL_Renderer* renderer, SDL_Window* window){
update_board     function    void update_board(SDL_Renderer* renderer){

render.c (funkcje pomocniczne przy renderowaniu)
draw_background  function    void draw_background(SDL_Renderer* renderer, SDL_Rect backgr){
end_game         function    int end_game(SDL_Renderer* renderer, SDL_Window* window) {

board.c (funkcje pomocniczne używające planszy)
clear            function    void clear(int y, int x, int color, struct cell board[ROWS][COLS]){
init_board       function    void init_board(float origin[], struct cell board[ROWS][COLS]){
is_falling       function    int is_falling(struct cell board[ROWS][COLS]){
move_block       function    void move_block(char d,struct cell board[ROWS][COLS]){
settle           function    void settle(int y, int x, struct cell board[ROWS][COLS]){
spawn_tetronimo  function    void spawn_tetronimo(int tetromino[4][4], int y, int x, struct cell board[ROWS][COLS]){
touch_wall_left  function    int touch_wall_left(struct cell board[ROWS][COLS]) {
touch_wall_right function    int touch_wall_right(struct cell board[ROWS][COLS]) {

Dodatkowo pliki `blocks.h` oraz `blocks.c` zawierają wszystkie możliwe ułożenia klocków (stałe)
```
