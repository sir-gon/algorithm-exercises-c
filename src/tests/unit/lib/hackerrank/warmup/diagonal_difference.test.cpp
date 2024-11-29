#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/diagonal_difference.h>
#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int **jsonToMatrix(const nlohmann::json &matrixJson, int &rows, int &cols) {
  // Extraer dimensiones
  rows = matrixJson.size();
  cols = rows > 0 ? matrixJson[0].size() : 0;

  // Crear matriz dinámica
  int **matrix = new int *[rows];
  for (int i = 0; i < rows; ++i) {
    matrix[i] = new int[cols];
    for (int j = 0; j < cols; ++j) {
      matrix[i][j] = matrixJson[i][j];
    }
  }

  return matrix;
}

void freeMatrix(int **matrix, int rows) {
  for (int i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

TEST_CASE("diagonalDifference JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() +
      "/unit/lib/hackerrank/warmup/diagonal_difference.testcases.json";

  INFO("diagonalDifference JSON test cases FILE: " << path);

  std::ifstream f(path);
  nlohmann::json testCases = nlohmann::json::parse(f);

  // Iterar sobre los casos de prueba
  for (const auto &testCase : testCases) {
    const auto &matrixJson = testCase["matrix"];
    int expected = testCase["expected"];

    int rows, cols;
    int **matrix = jsonToMatrix(matrixJson, rows, cols);

    // Llamar a la función bajo prueba
    int result = HACKERRANK_WARMUP_diagonalDifference(rows, cols, matrix);

    // Validar el resultado
    REQUIRE(result == expected);

    // Liberar memoria de la matriz
    freeMatrix(matrix, rows);
  }
}
