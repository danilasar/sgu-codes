using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StrangeCalculator
{
    
    public partial class MainWindow : Form
    {
        Dictionary<Calculator.Variable, VariableState<double>> vars;
        Calculator.Tabulator tabulator;
        private BindingList<Calculator.Equation> tabulatorBindingList;
        private BindingSource bindingSource;

        public MainWindow()
        {
            InitializeComponent();

            vars = new Dictionary<Calculator.Variable, VariableState<double>>() {
                { Calculator.Variable.x0, new VariableState<double>(0) },
                { Calculator.Variable.xk, new VariableState<double>(0) },
                { Calculator.Variable.dx, new VariableState<double>(0) },
                { Calculator.Variable.a, new VariableState<double>(0) }
            };
            tabulator = new Calculator.Tabulator();
            tabulator.OnEquationsChanged += () => UpdateResponse();
            tabulatorBindingList = new BindingList<Calculator.Equation>(tabulator.Equations);
            bindingSource = new BindingSource(tabulatorBindingList, null);
            tabulationsView.DataSource = bindingSource;
            textBoxX0.TextChanged += (o, e) => VariableChanged(Calculator.Variable.x0, textBoxX0.Text);
            textBoxXk.TextChanged += (o, e) => VariableChanged(Calculator.Variable.xk, textBoxXk.Text);
            textBoxDx.TextChanged += (o, e) => VariableChanged(Calculator.Variable.dx, textBoxDx.Text);
            textBoxA.TextChanged += (o, e) => VariableChanged(Calculator.Variable.a, textBoxA.Text);
        }

        private void UpdateResponse()
        {
            tabulationsView.Invoke(new MethodInvoker(delegate {
                tabulatorBindingList.ResetBindings();
            }));
            /*if (textBoxA.InvokeRequired){
                textBoxA.Invoke(new MethodInvoker(delegate { textBoxA.Text = result.ToString(); }));
            }*/
        }

        private void VariableChanged<T>(Calculator.Variable var, T new_value) where T : notnull
        {
            double res;
            if (new_value is double) {
                res = new_value as double? ?? 0;
            } else {
                if (!(new_value is string)
                    || !double.TryParse(new_value as string, out res)
                ) {
                    vars[var].IsGood = false;
                    return;
                }
            }
            vars[var].IsChanged = true;
            vars[var].IsGood = true;
            vars[var].Value = res;
            Task.Run(() => UpdateVariables());
        }

        /// <summary>
        /// Обновляет значения изменившихся переменных, если все они корректны
        /// </summary>
        private void UpdateVariables() {
            bool canUpdateCalculatorState = true;
            foreach(var var in vars) {
                canUpdateCalculatorState &= var.Value.IsGood;
            }
            if (!canUpdateCalculatorState) {
                return;
            }
            foreach(var var in vars) {
                if(var.Value.IsChanged) {
                    tabulator.Variables[var.Key] = var.Value.Value;
                }
            }
        }
    }
}
