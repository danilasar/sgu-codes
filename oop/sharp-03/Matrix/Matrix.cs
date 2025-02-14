using System;
using System.Collections.Generic;
using System.Text;

namespace Matrix
{
    public class Matrix<T>
    {
        private T[,] elements;
        public int Rows { get; private set; }
        public int Cols { get; private set; }

        // Конструктор, основанный на размерности матрицы
        public Matrix(int rows, int cols) {
            if (rows <= 0 || cols <= 0) {
                throw new ArgumentException("Размеры матрицы - это натуральное число");
            }

            Rows = rows;
            Cols = cols;
            elements = new T[rows, cols];
        }

        // Копирование с увеличением всех элементов на число
        public Matrix(Matrix<T> other, T difference)
        {
            Rows = other.Rows;
            Cols = other.Cols;
            elements = new T[Rows, Cols];
            dynamic diff = difference;
            for (int i = 0; i < Rows; i++) {
                for (int j = 0; j < Cols; j++) {
                    elements[i, j] = other.elements[i, j] + diff;
                }
            }
        }

        ~Matrix()
        {
            
        }

        // Обращение к элементам матрицы
        public T this[int row, int col] {
            get
            {
                if (row < 0 || row >= Rows || col < 0 || col >= Cols) {
                    throw new IndexOutOfRangeException();
                }
                return elements[row, col];
            }
            set
            {
                if (row < 0 || row >= Rows || col < 0 || col >= Cols) {
                    throw new IndexOutOfRangeException();
                }
                elements[row, col] = value;
            }
        }


        // Среднее элементов матрицы
        public double Average() {
            double sum = 0;
            dynamic elms = elements;
            for (int i = 0; i < Rows; i++) {
                for (int j = 0; j < Cols; j++) {
                    sum += (double)elms[i, j];
                }
            }
            return sum / (Rows * Cols);
        }


        // data2matrix
        public static explicit operator Matrix<T>(T value) {
            Matrix<T> matrix = new Matrix<T>(1, 1);
            matrix.elements[0, 0] = value;
            return matrix;
        }

        // matrix2double
        public static explicit operator double(Matrix<T> matrix) {
            return matrix.Average();
        }
    }

}
