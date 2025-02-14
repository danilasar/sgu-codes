using System;

namespace Matrix {
    class Program {
        static void Main(string[] args)
        {
            Matrix<double> d1 = (Matrix<double>)1.0;
            Matrix<double> d2 = new Matrix<double>(d1, 5);
            Matrix<double> d3 = new Matrix<double>(2, 2);
            d3[0, 0] = 1;
            d3[0, 1] = 2;
            d3[1, 0] = 3;
            d3[1, 1] = 4;
            Console.WriteLine((double)d3);
        }
    }
}
