using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrangeCalculator.Calculator
{
    /// <summary>
    /// Вычислитель, отвечающий за поиск значения функции при заданных x, b
    /// </summary>
    static class Calculator
    {
        /// <summary>
        /// Функция, вычисляющая y согласно актуальным значениям x и b
        /// </summary>
        public static double Calculate(double x, double b)
        {
            double b3 = b * b * b;

            double result = x;
            result += 15 * Math.Sqrt(x * x * x + b3);
            result *= 9;
            return result;
        }
    }
}
