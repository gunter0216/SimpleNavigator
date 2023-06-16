#include "ConsoleView.h"

ConsoleView::ConsoleView() {
  while (!stop_) {
    Loop();
  }
}

auto ConsoleView::Loop() -> void {
  PrintHelp();
  std::wcout << L"Введите число:" << std::endl;
  std::cin >> command_;
  switch (command_) {
    case 0:
      stop_ = true;
      break;
    case 1:
      Code1();
      break;
    case 2:
      Code2();
      break;
    case 3:
      Code3();
      break;
    case 4:
      Code4();
      break;
    case 5:
      Code5();
      break;
    case 6:
      Code6();
      break;
    case 7:
      Code7();
      break;
    case 8:
      Code8();
      break;
    case 9:
      PrintHelp();
      break;
    default:
      break;
  }
}

auto ConsoleView::Code1() -> void {
  std::wcout << L"Введите путь к файлу" << std::endl;
  std::string file_name;
  std::cin >> file_name;
  try {
    graph_.loadGraphFromFile(file_name);
    graph_.matrix().print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code2() -> void {
  std::wcout << L"Введите стартовую вершину" << std::endl;
  int start_vertex;
  std::cin >> start_vertex;
  try {
    auto que = graph_algorithms.breadthFirstSearch(graph_, start_vertex);
    que.print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code3() -> void {
  std::wcout << L"Введите стартовую вершину" << std::endl;
  int start_vertex;
  std::cin >> start_vertex;
  try {
    auto que = graph_algorithms.depthFirstSearch(graph_, start_vertex);
    que.print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code4() -> void {
  std::wcout << L"Введите начальную и конечную вершины" << std::endl;
  int vertex1, vertex2;
  std::cin >> vertex1 >> vertex2;
  try {
    auto value = graph_algorithms.getShortestPathBetweenVertices(
        graph_, vertex1, vertex2);
    std::wcout << value << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code5() -> void {
  try {
    auto matrix = graph_algorithms.getShortestPathsBetweenAllVertices(graph_);
    matrix.print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code6() -> void {
  try {
    auto graph = graph_algorithms.getLeastSpanningTree(graph_);
    graph.matrix().print();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code7() -> void {
  try {
    auto result = graph_algorithms.solveTravelingSalesmanProblem(graph_);
    for (auto item : result.vertices) std::wcout << item << " ";
    std::wcout << std::endl << result.distance << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code8() -> void {
  try {
    std::wcout << L"Введите кол-во раз выполнение алгоритмов" << std::endl;
    int N;
    std::cin >> N;
    for (int i = 0; i < 3; ++i) {
      Code8_algorithms(N, i);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

auto ConsoleView::Code8_algorithms(int n, int num) -> void {
  TsmResult result;
  switch (num) {
    case 0:
      std::wcout << L"Муравьиный алгоритм" << std::endl;
      break;
    case 1:
      std::wcout << L"Алгоритм отжига" << std::endl;
      break;
    case 2:
      std::wcout << L"Генетический алгоритм" << std::endl;
      break;
    default:
      break;
  }
  clock_t tStart = clock();
  for (int i = 0; i < n; ++i) {
    switch (num) {
      case 0:
        result = graph_algorithms.solveTravelingSalesmanProblem(graph_);
        break;
      case 1:
        result = graph_algorithms.solveTsmAnnealing(graph_);
        break;
      case 2:
        result = graph_algorithms.solveTsmGenetic(graph_);
        break;
      default:
        break;
    }
  }
  std::wcout << L"Время выполнения алгоритма: "
            << static_cast<double>(clock() - tStart) / CLOCKS_PER_SEC
            << std::endl;
  std::wcout << L"Маршрут: ";
  for (auto item : result.vertices) std::wcout << item << L" ";
  std::wcout << std::endl << L"Длина маршрута: " << result.distance << std::endl;
}

auto ConsoleView::PrintHelp() -> void {
  std::wcout << L"-------------------------------------------------------"
            << std::endl;
  std::wcout << L"1"
            << L" загрузка исходного графа из файла" << std::endl;
  std::wcout << "2"
            << L" обход графа в ширину с выводом результата обхода в консоль"
            << std::endl;
  std::wcout << L"3"
            << L" обход графа в глубину с выводом результата обхода в консоль"
            << std::endl;
  std::wcout << L"4"
            << L" поиск кратчайшего пути между произвольными двумя вершинами с "
               L"выводом результата в консоль"
            << std::endl;
  std::wcout << L"5"
            << L" поиск кратчайших путей между всеми парами вершин в графе с "
               L"выводом результирующей матрицы в консоль"
            << std::endl;
  std::wcout << L"6"
            << L" поиск минимального остовного дерева в графе с выводом "
               L"результирующей матрицы смежности в консоль"
            << std::endl;
  std::wcout << L"7"
            << L" решение задачи комивояжера с выводом результирующего маршрута "
               L"и его длины в консоль"
            << std::endl;
  std::wcout << L"8"
            << L" сравнение методов решения задачи коммивояжера" << std::endl;
  std::wcout << L"9"
            << L" help" << std::endl;
  std::wcout << L"0"
            << L" выйти" << std::endl;
  std::wcout << L"-------------------------------------------------------"
            << std::endl;
}
