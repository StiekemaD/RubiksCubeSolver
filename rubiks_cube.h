#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <array>
#include <iostream>
#include <vector>
#include <tuple>

enum class Move { F, Fi, B, Bi, R, Ri, L, Li, U, Ui, D, Di, RotLeft, RotRight };
using Face = std::array<std::array<int8_t, 3>, 3>;
using Cube = std::array<Face, 6>;

class Rubiks_cube
{
private:
    std::string colors[6] { "Yellow", "Orange", "Blue", "Red", "Green", "White" };
    Cube cube_;
    void turn_face(Face &face, bool invert = false);
    void move_F(bool invert = false);
    void move_B(bool invert = false);
    void move_R(bool invert = false);
    void move_U(bool invert = false);
    void move_D(bool invert = false);
    void move_L(bool invert = false);
    void rotate_cube(bool right = false);
public:
    Rubiks_cube();
    void doMove(Move m);
    void undoMove(Move m);
    void print(); // Leaving it in for debug
/*    bool hasWhiteCross();
    bool hasFirstTwoLayers();
    bool hasYellowCross();
    bool hasTopEdgesAligned();
    bool hasTopCornersAligned();
    bool isComplete();*/

    // new strategy
    int hasWhiteCross();
    int hasFirstTwoLayers();
    int hasYellowCross();
    int hasYellowCorners();
    int hasTopEdgesAligned();
    int hasTopCornersAligned();
    int isComplete();

    int getF2Lcorner();

    std::string getFaceColor(int face, int x, int y) { return colors[cube_[face][x][y]]; }
    friend bool operator<(const Rubiks_cube &cube1, const Rubiks_cube &cube2);
};

#endif // RUBIKS_CUBE_H
