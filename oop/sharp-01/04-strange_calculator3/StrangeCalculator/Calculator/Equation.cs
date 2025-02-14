using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrangeCalculator.Calculator
{
    public class Equation
    {
        public double x { get; set; }
        public double y { get; set; }
        public Equation(double x, double y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
