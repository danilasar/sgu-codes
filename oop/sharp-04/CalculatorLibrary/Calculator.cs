using System;

namespace CalculatorLibrary
{
    public enum Comparator
    {
        AB,
        CD
    }
    public class Variant
    {
        private Comparator Pair;
        private double Value;
        public Variant(Comparator pair, double value) {
            Pair = pair;
            Value = value;
        }

        public Comparator GetPair() {
            return Pair;
        }

        public double GetValue() {
            return Value;
        }
    }
    public class Calculator
    {
        public static int SqrSum(int x = 0, int y = 0) {
            return x * x + y * y;
        }
        public static double SqrSum(double x = 0, double y = 0) {
            return x * x + y * y;
        }
        public static long SqrSum(long x = 0, long y = 0) {
            return x * x + y * y;
        }
        public static int SqrSum(short x = 0, short y = 0) {
            return x * x + y * y;
        }

        public static Variant GetMax(Tuple<double, double> ab, Tuple<double, double> cd) {
            double abResult = SqrSum(ab.Item1, ab.Item2);
            double cdResult = SqrSum(cd.Item1, cd.Item2);
            if(abResult >= cdResult) {
                return new Variant(Comparator.AB, abResult);
            }
            return new Variant(Comparator.CD, cdResult);
        }
    }
}
