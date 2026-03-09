#include "Frontend/LevelEditor.h"

#include <algorithm>
#include <imgui.h>
#include <fstream>
#include <sstream>

namespace
{
    constexpr int MIN_GRID_SIZE = 1;
    constexpr int MAX_GRID_SIZE = 128;
    constexpr int MIN_TILE_TYPE = 0;
    constexpr int MAX_TILE_TYPE = 10;
}

LevelEditor::LevelEditor()
    : rows(6), cols(8), selectedTile(1)
{
    ResizeGrid(rows, cols);
}

void LevelEditor::ResizeGrid(int newRows, int newCols)
{
    rows = std::clamp(newRows, MIN_GRID_SIZE, MAX_GRID_SIZE);
    cols = std::clamp(newCols, MIN_GRID_SIZE, MAX_GRID_SIZE);
    grid.assign(static_cast<size_t>(rows) * static_cast<size_t>(cols), 0);
}

void LevelEditor::DrawGUI()
{
    ImGui::Begin("Level Editor");

    ImGui::InputInt("Rows", &rows);
    ImGui::InputInt("Cols", &cols);
    if (ImGui::Button("Resize"))
        ResizeGrid(rows, cols);

    ImGui::Separator();

    ImGui::InputInt("Tile Type", &selectedTile);
    selectedTile = std::clamp(selectedTile, MIN_TILE_TYPE, MAX_TILE_TYPE);

    ImGui::Separator();

    if (ImGui::Button("Save Level"))
        SaveToFile("level1.txt");

    ImGui::SameLine();

    if (ImGui::Button("Load Level"))
        LoadFromFile("level1.txt");

    ImGui::Separator();
    RenderGrid();

    ImGui::End();
}

void LevelEditor::RenderGrid()
{
    const float cellSize = 32.0f;
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            ImGui::PushID(r * cols + c);
            ImGui::Button(std::to_string(grid[r * cols + c]).c_str(), ImVec2(cellSize, cellSize));
            if (ImGui::IsItemHovered() && ImGui::IsMouseDown(0))
                grid[r * cols + c] = selectedTile;
            ImGui::PopID();
            if (c < cols - 1)
                ImGui::SameLine();
        }
    }
}

void LevelEditor::SaveToFile(const std::string& filename)
{
    std::ofstream out(filename);
    if (!out.is_open()) return;

    out << rows << " " << cols << "\n";
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            out << grid[r * cols + c] << " ";
        }
        out << "\n";
    }
}

void LevelEditor::LoadFromFile(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in.is_open()) return;

    in >> rows >> cols;
    ResizeGrid(rows, cols);

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            int tile;
            in >> tile;
            grid[r * cols + c] = std::clamp(tile, MIN_TILE_TYPE, MAX_TILE_TYPE);
        }
    }
}
