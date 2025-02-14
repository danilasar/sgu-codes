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
        /// <summary>
        /// Словарь с переменныи, где ключ --- строковое имя, значение --- объект состояния
        /// </summary>
        Dictionary<string, Variable> vars;
        /// <summary>
        /// Объект вычислителя, отвечающий за бизнес-логику программы
        /// </summary>
        Calculator calculator;
        public MainWindow()
        {
            InitializeComponent();
            textBoxX.TextChanged += (o, e) => VariableValueChanged("x", textBoxX.Text);
            textBoxY.TextChanged += (o, e) => VariableValueChanged("y", textBoxY.Text);
            textBoxZ.TextChanged += (o, e) => VariableValueChanged("z", textBoxZ.Text);
            vars = new Dictionary<string, Variable> {
                { "x", new Variable() }, { "y", new Variable() }, { "z", new Variable() }
            };
            calculator = new Calculator();
            calculator.OnValueChanged += UpdateResponse;
            textBoxX.Text = 16.55e-3.ToString();
            textBoxY.Text = "-2,75";
            textBoxZ.Text = "0,15";

        }

        private void UpdateResponse(double result)
        {
            if (textBoxBeta.InvokeRequired){
                textBoxBeta.Invoke(new MethodInvoker(delegate { textBoxBeta.Text = result.ToString(); }));
            }
        }

        /// <summary>
        /// Обработчик событий обновления введённого текста в TextBox подцепляет введённое число и, если удаётся его привести к дублю, обновляет значения переменных.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void VariableValueChanged(string var, string new_value)
        {
            double res;
            vars[var].IsChanged = true;
            if (!double.TryParse(new_value, out res)) {
                vars[var].IsGood = false;
                return;
            }
            vars[var].IsGood = true;
            vars[var].Value = res;
            Task.Run(() => UpdateVariables());
        }
        /// <summary>
        /// Обновляет значения изменившихся переменных, если все они корректны
        /// </summary>
        private void UpdateVariables() {
            bool canUpdateCalculatorState = true;
            foreach (KeyValuePair<string, Variable> kv in vars) {
                canUpdateCalculatorState &= kv.Value.IsGood;
            }
            if (!canUpdateCalculatorState) {
                return;
            }
            foreach (KeyValuePair<string, Variable> kv in vars) {
                if (kv.Value.IsChanged) {
                    calculator.ChangeVariable(kv.Key, kv.Value.Value);
                    kv.Value.IsChanged = false;
                }
            }
        }
    }
}
