CCX= g++ -Wall -Werror -Wextra -std=c++17

main: s21_matrix_oop.a

s21_matrix_oop.a:
	$(CCX) s21_matrix_oop.cpp -c
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	rm s21_matrix_oop.o

clean:
	rm -rf *.out *.gcda *.gcno *.info gcov_report/ *.a *.o a.out.dSYM test

.PHONY: s21_matrix_oop.a clean