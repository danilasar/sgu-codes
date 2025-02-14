using System;
using System.Reflection;

namespace DynamicConsoleCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Assembly a = Assembly.LoadFrom("CalculatorLibrary.dll");
            Type Calculator = a.GetType("CalculatorLibrary.Calculator", true, true);
            MethodInfo GetMax = Calculator.GetMethod("GetMax");
            object result = GetMax.Invoke(null, new object[] {
                new Tuple<double, double>(1, 2),
                new Tuple<double, double>(3, 4)
            });
            Type Variant = a.GetType("CalculatorLibrary.Variant", true, true);
            MethodInfo VariantValue = Variant.GetMethod("GetValue");
            double resultValue = VariantValue.Invoke(result, null) as double? ?? 0;
            Console.WriteLine(resultValue);
        }
    }
}
