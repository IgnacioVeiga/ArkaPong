#pragma once

#include <vector>
#include <string>

class LevelEditor
{
public:
    LevelEditor();

    void DrawGUI();
    void RenderGrid();
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

private:
    int rows, cols;
    int selectedTile;
    std::vector<int> grid;   // grid[row * cols + col]

    void ResizeGrid(int newRows, int newCols);
};
