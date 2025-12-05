CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -lgtest -lgtest_main -pthread

# Флаги для покрытия кода
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
COVERAGE_LIBS = -lgcov

# Основные цели
TARGET = matrix_tests
TARGET_COVERAGE = matrix_tests_coverage
SOURCES = Matrix.cpp MatrixTests.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Правила компиляции
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(TARGET_COVERAGE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -o $(TARGET_COVERAGE) $(SOURCES) $(LDFLAGS) $(COVERAGE_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Тестирование
test: $(TARGET)
	./$(TARGET)

# Покрытие кода (только gcovr версия которая работает)
coverage-gcovr: $(TARGET_COVERAGE)
	./$(TARGET_COVERAGE)
	@which gcovr > /dev/null 2>&1 || (echo "Installing gcovr..." && sudo apt-get install -y gcovr)
	gcovr --root . --exclude "tests/" --exclude "/usr/" --print-summary
	gcovr --root . --exclude "tests/" --exclude "/usr/" --html-details coverage_gcovr.html
	@echo "Coverage report generated in coverage_gcovr.html"

# Псевдоним для простоты
coverage: coverage-gcovr

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET_COVERAGE)
	rm -f *.gcda *.gcno *.gcov
	rm -f coverage_gcovr.html

# Установка зависимостей
deps:
	sudo apt update
	sudo apt install -y build-essential libgtest-dev gcovr

.PHONY: all test coverage coverage-gcovr clean deps
