#include "rubiks_cube.h"

Rubiks_cube::Rubiks_cube()
{
    for(int8_t i = 0; i < 6; i++) {
        cube_[i] = {{  {{ i, i, i }}, {{ i, i, i }}, {{ i, i, i }}  }};
    }
}
/*
bool Rubiks_cube::hasWhiteCross() {
    if(cube_[5][0][1] != cube_[5][1][1] || cube_[5][2][1] != cube_[5][1][1] || cube_[5][1][0] != cube_[5][1][1] || cube_[5][1][2] != cube_[5][1][1]) { return false; }
    if(cube_[1][2][1] != cube_[1][1][1] || cube_[2][2][1] != cube_[2][1][1] || cube_[3][2][1] != cube_[3][1][1] || cube_[4][2][1] != cube_[4][1][1]) { return false; }
    return true;
}

bool Rubiks_cube::hasFirstTwoLayers() {
    if(cube_[5][0][0] != cube_[5][1][1] || cube_[5][0][2] != cube_[5][1][1] || cube_[5][2][0] != cube_[5][1][1] || cube_[5][2][2] != cube_[5][1][1]) { return false; }
    for(int i = 1; i < 5; i++) {
        if(cube_[i][1][0] != cube_[i][1][1] || cube_[i][2][0] != cube_[i][1][1] || cube_[i][1][2] != cube_[i][1][1] || cube_[i][2][2] != cube_[i][1][1]) { return false; }
    }
    return hasWhiteCross();
}

bool Rubiks_cube::hasYellowCross() {
    if(cube_[0][0][1] != cube_[0][1][1] || cube_[0][2][1] != cube_[0][1][1] || cube_[0][1][0] != cube_[0][1][1] || cube_[0][1][2] != cube_[0][1][1]) { return false; }
    return true;
}

bool Rubiks_cube::hasTopCornersAligned() {
    if(cube_[0][0][0] != cube_[0][1][1] && cube_[0][0][0] != cube_[1][1][1] && cube_[0][0][0] != cube_[4][1][1] || cube_[1][0][0] != cube_[0][1][1] && cube_[1][0][0] != cube_[1][1][1] && cube_[1][0][0] != cube_[4][1][1] || cube_[4][0][2] != cube_[0][1][1] && cube_[4][0][2] != cube_[1][1][1] && cube_[4][0][2] != cube_[4][1][1]) { return false; }
    if(cube_[0][0][2] != cube_[0][1][1] && cube_[0][0][2] != cube_[3][1][1] && cube_[0][0][2] != cube_[4][1][1] || cube_[3][0][2] != cube_[0][1][1] && cube_[3][0][2] != cube_[3][1][1] && cube_[3][0][2] != cube_[4][1][1] || cube_[4][0][0] != cube_[0][1][1] && cube_[4][0][0] != cube_[3][1][1] && cube_[4][0][0] != cube_[4][1][1]) { return false; }
    if(cube_[0][2][0] != cube_[0][1][1] && cube_[0][2][0] != cube_[2][1][1] && cube_[0][2][0] != cube_[1][1][1] || cube_[1][0][2] != cube_[0][1][1] && cube_[1][0][2] != cube_[2][1][1] && cube_[1][0][2] != cube_[1][1][1] || cube_[2][0][0] != cube_[0][1][1] && cube_[2][0][0] != cube_[2][1][1] && cube_[2][0][0] != cube_[1][1][1]) { return false; }
    if(cube_[0][2][2] != cube_[0][1][1] && cube_[0][2][2] != cube_[2][1][1] && cube_[0][2][2] != cube_[3][1][1] || cube_[2][0][2] != cube_[0][1][1] && cube_[2][0][2] != cube_[2][1][1] && cube_[2][0][2] != cube_[3][1][1] || cube_[3][0][0] != cube_[0][1][1] && cube_[3][0][0] != cube_[2][1][1] && cube_[3][0][0] != cube_[3][1][1]) { return false; }
    return true;
}

bool Rubiks_cube::hasTopEdgesAligned() {
    if(cube_[0][2][1] != cube_[0][1][1] && cube_[0][2][1] != cube_[2][1][1] || cube_[2][0][1] != cube_[0][1][1] && cube_[2][0][1] != cube_[2][1][1]) { return false; }
    if(cube_[0][1][0] != cube_[0][1][1] && cube_[0][1][0] != cube_[1][1][1] || cube_[1][0][1] != cube_[0][1][1] && cube_[1][0][1] != cube_[1][1][1]) { return false; }
    if(cube_[0][0][1] != cube_[0][1][1] && cube_[0][0][1] != cube_[4][1][1] || cube_[4][0][1] != cube_[0][1][1] && cube_[4][0][1] != cube_[4][1][1]) { return false; }
    if(cube_[0][1][2] != cube_[0][1][1] && cube_[0][2][1] != cube_[3][1][1] || cube_[3][0][1] != cube_[0][1][1] && cube_[3][0][1] != cube_[3][1][1]) { return false; }
    return true;
}

bool Rubiks_cube::isComplete() {
    if(!hasYellowCross()) { return false; }
    if(cube_[0][0][0] != cube_[0][1][1] || cube_[0][0][2] != cube_[0][1][1] || cube_[0][2][0] != cube_[0][1][1] || cube_[0][2][2] != cube_[0][1][1]) { return false; }
    if(!hasTopCornersAligned() || !hasTopEdgesAligned()) { return false; }
    return hasFirstTwoLayers();
}
*/
// new strategy
int Rubiks_cube::hasWhiteCross() {
    int score = 0;
    if(cube_[1][2][1] == cube_[1][1][1] && cube_[5][1][0] == cube_[5][1][1]) score++;
    if(cube_[2][2][1] == cube_[2][1][1] && cube_[5][0][1] == cube_[5][1][1]) score++;
    if(cube_[3][2][1] == cube_[3][1][1] && cube_[5][1][2] == cube_[5][1][1]) score++;
    if(cube_[4][2][1] == cube_[4][1][1] && cube_[5][2][1] == cube_[5][1][1]) score++;
    return score;
}

int Rubiks_cube::hasFirstTwoLayers() {
    int score = 0;
    if(cube_[5][0][0] == cube_[5][1][1] && cube_[1][2][2] == cube_[1][1][1] && cube_[1][1][2] == cube_[1][1][1] && cube_[2][2][0] == cube_[2][1][1] && cube_[2][1][0] == cube_[2][1][1]) score++;
    if(cube_[5][2][0] == cube_[5][1][1] && cube_[1][2][0] == cube_[1][1][1] && cube_[1][1][0] == cube_[1][1][1] && cube_[4][2][2] == cube_[4][1][1] && cube_[4][1][2] == cube_[4][1][1]) score++;
    if(cube_[5][0][2] == cube_[5][1][1] && cube_[2][2][2] == cube_[2][1][1] && cube_[2][1][2] == cube_[2][1][1] && cube_[3][2][0] == cube_[3][1][1] && cube_[3][1][0] == cube_[3][1][1]) score++;
    if(cube_[5][2][2] == cube_[5][1][1] && cube_[3][2][2] == cube_[3][1][1] && cube_[3][1][2] == cube_[3][1][1] && cube_[4][2][0] == cube_[4][1][1] && cube_[4][1][0] == cube_[4][1][1]) score++;
    return score + this->hasWhiteCross();
}

int Rubiks_cube::getF2Lcorner() {
    if(!(cube_[5][0][0] == cube_[5][1][1] && cube_[1][2][2] == cube_[1][1][1] && cube_[1][1][2] == cube_[1][1][1] && cube_[2][2][0] == cube_[2][1][1] && cube_[2][1][0] == cube_[2][1][1])) return 1;
    if(!(cube_[5][2][0] == cube_[5][1][1] && cube_[1][2][0] == cube_[1][1][1] && cube_[1][1][0] == cube_[1][1][1] && cube_[4][2][2] == cube_[4][1][1] && cube_[4][1][2] == cube_[4][1][1])) return 3;
    if(!(cube_[5][0][2] == cube_[5][1][1] && cube_[2][2][2] == cube_[2][1][1] && cube_[2][1][2] == cube_[2][1][1] && cube_[3][2][0] == cube_[3][1][1] && cube_[3][1][0] == cube_[3][1][1])) return 2;
    if(!(cube_[5][2][2] == cube_[5][1][1] && cube_[3][2][2] == cube_[3][1][1] && cube_[3][1][2] == cube_[3][1][1] && cube_[4][2][0] == cube_[4][1][1] && cube_[4][1][0] == cube_[4][1][1])) return 4;
}

int Rubiks_cube::hasYellowCross() {
    if(cube_[0][0][1] != cube_[0][1][1] || cube_[0][2][1] != cube_[0][1][1] || cube_[0][1][0] != cube_[0][1][1] || cube_[0][1][2] != cube_[0][1][1]) { return false; }
    return true;
}

int Rubiks_cube::hasYellowCorners() {
    if(cube_[0][0][0] != cube_[0][1][1] || cube_[0][0][2] != cube_[0][1][1] || cube_[0][2][0] != cube_[0][1][1] || cube_[0][2][2] != cube_[0][1][1]) { return false; }
    return true;
}

int Rubiks_cube::hasTopCornersAligned() {
    if(cube_[0][0][0] != cube_[0][1][1] && cube_[0][0][0] != cube_[1][1][1] && cube_[0][0][0] != cube_[4][1][1] || cube_[1][0][0] != cube_[0][1][1] && cube_[1][0][0] != cube_[1][1][1] && cube_[1][0][0] != cube_[4][1][1] || cube_[4][0][2] != cube_[0][1][1] && cube_[4][0][2] != cube_[1][1][1] && cube_[4][0][2] != cube_[4][1][1]) { return false; }
    if(cube_[0][0][2] != cube_[0][1][1] && cube_[0][0][2] != cube_[3][1][1] && cube_[0][0][2] != cube_[4][1][1] || cube_[3][0][2] != cube_[0][1][1] && cube_[3][0][2] != cube_[3][1][1] && cube_[3][0][2] != cube_[4][1][1] || cube_[4][0][0] != cube_[0][1][1] && cube_[4][0][0] != cube_[3][1][1] && cube_[4][0][0] != cube_[4][1][1]) { return false; }
    if(cube_[0][2][0] != cube_[0][1][1] && cube_[0][2][0] != cube_[2][1][1] && cube_[0][2][0] != cube_[1][1][1] || cube_[1][0][2] != cube_[0][1][1] && cube_[1][0][2] != cube_[2][1][1] && cube_[1][0][2] != cube_[1][1][1] || cube_[2][0][0] != cube_[0][1][1] && cube_[2][0][0] != cube_[2][1][1] && cube_[2][0][0] != cube_[1][1][1]) { return false; }
    if(cube_[0][2][2] != cube_[0][1][1] && cube_[0][2][2] != cube_[2][1][1] && cube_[0][2][2] != cube_[3][1][1] || cube_[2][0][2] != cube_[0][1][1] && cube_[2][0][2] != cube_[2][1][1] && cube_[2][0][2] != cube_[3][1][1] || cube_[3][0][0] != cube_[0][1][1] && cube_[3][0][0] != cube_[2][1][1] && cube_[3][0][0] != cube_[3][1][1]) { return false; }
    return true;
}

int Rubiks_cube::hasTopEdgesAligned() {
    if(cube_[0][2][1] != cube_[0][1][1] && cube_[0][2][1] != cube_[2][1][1] || cube_[2][0][1] != cube_[0][1][1] && cube_[2][0][1] != cube_[2][1][1]) { return false; }
    if(cube_[0][1][0] != cube_[0][1][1] && cube_[0][1][0] != cube_[1][1][1] || cube_[1][0][1] != cube_[0][1][1] && cube_[1][0][1] != cube_[1][1][1]) { return false; }
    if(cube_[0][0][1] != cube_[0][1][1] && cube_[0][0][1] != cube_[4][1][1] || cube_[4][0][1] != cube_[0][1][1] && cube_[4][0][1] != cube_[4][1][1]) { return false; }
    if(cube_[0][1][2] != cube_[0][1][1] && cube_[0][2][1] != cube_[3][1][1] || cube_[3][0][1] != cube_[0][1][1] && cube_[3][0][1] != cube_[3][1][1]) { return false; }
    return true;
}

int Rubiks_cube::isComplete() {
    if(!hasYellowCross()) { return false; }
    if(!hasYellowCorners()) { return false; }
    if(!hasTopCornersAligned() || !hasTopEdgesAligned()) { return false; }
    return hasFirstTwoLayers();
}


void Rubiks_cube::doMove(Move m) {
    switch(m) {
        case Move::B: { move_B(); return; }
        case Move::F: { move_F(); return; }
        case Move::R: { move_R(); return; }
        case Move::L: { move_L(); return; }
        case Move::U: { move_U(); return; }
        case Move::D: { move_D(); return; }
        case Move::Bi: { move_B(true); return; }
        case Move::Fi: { move_F(true); return; }
        case Move::Ri: { move_R(true); return; }
        case Move::Li: { move_L(true); return; }
        case Move::Ui: { move_U(true); return; }
        case Move::Di: { move_D(true); return; }
        case Move::RotLeft: { rotate_cube(); return; }
        case Move::RotRight: { rotate_cube(true); return; }
    }
}

void Rubiks_cube::undoMove(Move m) {
    switch(m) {
        case Move::B: { move_B(true); return; }
        case Move::F: { move_F(true); return; }
        case Move::R: { move_R(true); return; }
        case Move::L: { move_L(true); return; }
        case Move::U: { move_U(true); return; }
        case Move::D: { move_D(true); return; }
        case Move::Bi: { move_B(); return; }
        case Move::Fi: { move_F(); return; }
        case Move::Ri: { move_R(); return; }
        case Move::Li: { move_L(); return; }
        case Move::Ui: { move_U(); return; }
        case Move::Di: { move_D(); return; }
        case Move::RotLeft: { rotate_cube(true); return; }
        case Move::RotRight: { rotate_cube(); return; }
    }
}

void Rubiks_cube::print()
{
    int i, j, k;

    for(i = 0; i < cube_[0].size(); i++) {
        std::cout << "      ";
        for(j = 0; j < cube_[0][i].size(); j++) {
            std::cout << cube_[0][i][j] << " ";
        }
        std::cout << "\n";
    }

    for(i = 0; i < 3; i++) {
        for(j = 1; j < 5; j++) {
            for(k = 0; k < cube_[j][i].size(); k++) {
                std::cout << cube_[j][i][k] << " ";
            }
        }
        std::cout << "\n";
    }

    for(i = 0; i < cube_[5].size(); i++) {
        std::cout << "      ";
        for(j = 0; j < cube_[5][i].size(); j++) {
            std::cout << cube_[5][i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Rubiks_cube::turn_face(Face &face, bool invert)
{
    if(invert) {
        int temp = face[0][2];
        face[0][2] = face[2][2];
        face[2][2] = face[2][0];
        face[2][0] = face[0][0];
        face[0][0] = temp;
        temp = face[1][2];
        face[1][2] = face[2][1];
        face[2][1] = face[1][0];
        face[1][0] = face[0][1];
        face[0][1] = temp;
    } else {
        int temp = face[0][2];
        face[0][2] = face[0][0];
        face[0][0] = face[2][0];
        face[2][0] = face[2][2];
        face[2][2] = temp;
        temp = face[1][2];
        face[1][2] = face[0][1];
        face[0][1] = face[1][0];
        face[1][0] = face[2][1];
        face[2][1] = temp;
    }
}

void Rubiks_cube::move_R(bool invert)
{
    int i, temp;
    turn_face(cube_[3], invert);
    if(invert) {
        for(i = cube_[3].size() - 1; i >= 0; i--) {
            temp = cube_[0][i][2];
            cube_[0][i][2] = cube_[4][2 - i][0];
            cube_[4][2 - i][0] = cube_[5][i][2];
            cube_[5][i][2] = cube_[2][i][2];
            cube_[2][i][2] = temp;
        }
    } else {
        for(i = 0; i < cube_[3].size(); i++) {
            temp = cube_[0][i][2];
            cube_[0][i][2] = cube_[2][i][2];
            cube_[2][i][2] = cube_[5][i][2];
            cube_[5][i][2] = cube_[4][2 - i][0];
            cube_[4][2 - i][0] = temp;
        }
    }
}

void Rubiks_cube::move_L(bool invert)
{
    int i, temp;
    turn_face(cube_[1], invert);
    if(invert) {
        for(i = cube_[1].size() - 1; i >= 0; i--) {
            temp = cube_[0][i][0];
            cube_[0][i][0] = cube_[2][i][0];
            cube_[2][i][0] = cube_[5][i][0];
            cube_[5][i][0] = cube_[4][2 - i][2];
            cube_[4][2 - i][2] = temp;
        }
    } else {
        for(i = 0; i < cube_[1].size(); i++) {
            temp = cube_[0][i][0];
            cube_[0][i][0] = cube_[4][2 - i][2];
            cube_[4][2 - i][2] = cube_[5][i][0];
            cube_[5][i][0] = cube_[2][i][0];
            cube_[2][i][0] = temp;
        }
    }
}


void Rubiks_cube::move_F(bool invert)
{
    int i, temp;
    turn_face(cube_[2], invert);
    if(invert) {
        for(i = cube_[2].size() - 1; i >= 0; i--) {
            temp = cube_[0][2][i];
            cube_[0][2][i] = cube_[3][i][0];
            cube_[3][i][0] = cube_[5][0][2 - i];
            cube_[5][0][2 - i] = cube_[1][2 - i][2];
            cube_[1][2 - i][2] = temp;
        }
    } else {
        for(i = 0; i < cube_[2].size(); i++) {
            temp = cube_[0][2][i];
            cube_[0][2][i] = cube_[1][2 - i][2];
            cube_[1][2 - i][2] = cube_[5][0][2 - i];
            cube_[5][0][2 - i] = cube_[3][i][0];
            cube_[3][i][0] = temp;
        }
    }
}

void Rubiks_cube::move_B(bool invert)
{
    int i, temp;
    turn_face(cube_[4], invert);
    if(invert) {
        for(i = cube_[4].size() -1; i >= 0; i--) {
            temp = cube_[0][0][2 - i];
            cube_[0][0][2 - i] = cube_[1][i][0];
            cube_[1][i][0] = cube_[5][2][i];
            cube_[5][2][i] = cube_[3][2 - i][2];
            cube_[3][2 - i][2] = temp;
        }
    } else {
        for(i = 0; i < cube_[4].size(); i++) {
            temp = cube_[0][0][i];
            cube_[0][0][i] = cube_[3][i][2];
            cube_[3][i][2] = cube_[5][2][2 - i];
            cube_[5][2][2 - i] = cube_[1][2 - i][0];
            cube_[1][2 - i][0] = temp;
        }
    }
}

void Rubiks_cube::move_D(bool invert)
{
    int i, temp;
    turn_face(cube_[5], invert);
    if(invert) {
        for(i = cube_[5].size() -1; i >= 0; i--) {
            temp = cube_[4][2][i];
            cube_[4][2][i] = cube_[1][2][i];
            cube_[1][2][i] = cube_[2][2][i];
            cube_[2][2][i] = cube_[3][2][i];
            cube_[3][2][i] = temp;
        }
    } else {
        for(i = 0; i < cube_[5].size(); i++) {
            temp = cube_[4][2][i];
            cube_[4][2][i] = cube_[3][2][i];
            cube_[3][2][i] = cube_[2][2][i];
            cube_[2][2][i] = cube_[1][2][i];
            cube_[1][2][i] = temp;
        }
    }
}

void Rubiks_cube::move_U(bool invert)
{
    int i, temp;
    turn_face(cube_[0], invert);
    if(invert) {
        for(i = cube_[0].size() -1; i >= 0; i--) {
            temp = cube_[4][0][i];
            cube_[4][0][i] = cube_[3][0][i];
            cube_[3][0][i] = cube_[2][0][i];
            cube_[2][0][i] = cube_[1][0][i];
            cube_[1][0][i] = temp;
        }
    } else {
        for(i = 0; i < cube_[0].size(); i++) {
            temp = cube_[4][0][i];
            cube_[4][0][i] = cube_[1][0][i];
            cube_[1][0][i] = cube_[2][0][i];
            cube_[2][0][i] = cube_[3][0][i];
            cube_[3][0][i] = temp;
        }
    }
}

void Rubiks_cube::rotate_cube(bool right)
{
    Face temp;
    if(right) {
        turn_face(cube_[0], true);
        turn_face(cube_[5], false);
        temp = cube_[1];
        cube_[1] = cube_[4];
        cube_[4] = cube_[3];
        cube_[3] = cube_[2];
        cube_[2] = temp;
    } else {
        turn_face(cube_[0], false);
        turn_face(cube_[5], true);
        temp = cube_[1];
        cube_[1] = cube_[2];
        cube_[2] = cube_[3];
        cube_[3] = cube_[4];
        cube_[4] = temp;
    }
}

/*
    cube_[0] = {{  {{ 1, 2, 3 }},
                   {{ 4, 5, 6 }},
                   {{ 7, 8, 9 }}  }};

    cube_[1] = {{  {{ 1, 2, 3 }},
                   {{ 4, 5, 6 }},
                   {{ 7, 8, 9 }}  }};

    cube_[2] = {{  {{ 1, 2, 3 }},
                   {{ 4, 5, 6 }},
                   {{ 7, 8, 9 }}  }};

    cube_[3] = {{  {{ 1, 2, 3 }},
                   {{ 4, 5, 6 }},
                   {{ 7, 8, 9 }}  }};

    cube_[4] = {{  {{ 1, 2, 3 }},
                   {{ 4, 5, 6 }},
                   {{ 7, 8, 9 }}  }};

    cube_[5] = {{  {{ 1, 2, 3 }},
                   {{ 4, 5, 6 }},
                   {{ 7, 8, 9 }}  }};
*/
