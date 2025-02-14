using System;
using System.Collections.Generic;
using System.Text;

namespace CalculatorLibrary
{
    public static class ReverseExtension
    {
        public static int Reverse(this int x) {
            int result = 0;
            while(x > 0)  {
                result *= 10;
                result += x % 10;
                x /= 10;
            }
            return result;
        }
    }
}
