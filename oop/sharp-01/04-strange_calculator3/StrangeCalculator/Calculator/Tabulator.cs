using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StrangeCalculator.Calculator
{
    public class Tabulator
    {
        public VariablesIndexer<double> Variables;

        public List<Equation> Equations { get; private set; }

        public delegate void EquationEvent();

        public EquationEvent OnEquationsChanged;

        public Tabulator()
        {
            Variables = new VariablesIndexer<double>();
            Equations = new List<Equation>();
            Variables.OnVariableChanged += (var, val) => Task.Run(() => Recalculate());
        }

        private bool Check()
        {
            double x0 = Variables[Variable.x0];
            double xk = Variables[Variable.xk];
            double dx = Variables[Variable.dx];
            return Math.Sign(xk - x0) == Math.Sign(dx) && dx != 0;
        }

        private void Recalculate()
        {
            if(!Check()) {
                return;
            }
            Equations.Clear();
            for(double x = Variables[Variable.x0]; x <= Variables[Variable.xk]; x += Variables[Variable.dx]) {
                Equations.Add(new Equation(x, Calculator.Calculate(x, Variables[Variable.a])));
            }
            if (Equations.Last().x != Variables[Variable.xk]) {
                Equations.Add(new Equation(Variables[Variable.xk], Calculator.Calculate(Variables[Variable.xk], Variables[Variable.a])));
            }

            OnEquationsChanged?.Invoke();
        }
    }
}
