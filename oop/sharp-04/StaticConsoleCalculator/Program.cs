using System;
using CalculatorLibrary;

namespace StaticConsoleCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            double max = Calculator.GetMax(
                new Tuple<double, double>(1, 2),
                new Tuple<double, double>(3, 4)
            ).GetValue();
            
            Console.WriteLine(max);

            int aboba = 123;
            aboba.Reverse();

            Console.WriteLine(aboba);
        }
    }
}
