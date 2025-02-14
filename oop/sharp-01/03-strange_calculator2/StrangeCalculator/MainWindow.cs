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
    enum FunctionType {
        SH,
        SQR,
        EXPONENT
    }
    public partial class MainWindow : Form
    {
        VariableState<double> varX, varB;
        VariableState<FunctionType> funcF;

        /// <summary>
        /// Объект вычислителя, отвечающий за бизнес-логику программы
        /// </summary>
        Calculator calculator;
        public MainWindow()
        {
            InitializeComponent();
            textBoxX.TextChanged += (o, e) => ArgumentsStateChanged("x", textBoxX.Text);
            textBoxB.TextChanged += (o, e) => ArgumentsStateChanged("b", textBoxB.Text);
            radioE.CheckedChanged += (o, e) => FunctionChanged();
            radioSh.CheckedChanged += (o, e) => FunctionChanged();
            radioSq.CheckedChanged += (o, e) => FunctionChanged();
            varX = new VariableState<double>(0);
            varB = new VariableState<double>(0);
            funcF = new VariableState<FunctionType>(FunctionType.SH);
            calculator = new Calculator();
            calculator.OnValueChanged += UpdateResponse;
            radioSh.Checked = true;
        }

        private void UpdateResponse(double result)
        {
            if (textBoxG.InvokeRequired){
                textBoxG.Invoke(new MethodInvoker(delegate { textBoxG.Text = result.ToString(); }));
            }
        }

        private void ArgumentsStateChanged<T>(string var, T new_value) where T : notnull
        {
            switch(var) {
                case "x":
                    VariableChanged(ref varX, new_value);
                    break;
                case "b":
                    VariableChanged(ref varB, new_value);
                    break;
                case "f":
                    if (!(new_value is FunctionType?)) {
                        funcF.IsGood = false;
                        return;
                    }
                    FunctionType res = new_value as FunctionType? ?? FunctionType.SH;
                    funcF.IsChanged = true;
                    funcF.IsGood = true;
                    funcF.Value = res;
                    break;
                default:
                    throw new MissingMemberException(var);
            }
            Task.Run(() => UpdateVariables());
        }

        private void VariableChanged<T>(ref VariableState<double> var, T new_value) where T : notnull
        {
            double res;
            if (new_value is double) {
                res = new_value as double? ?? 0;
            } else {
                if (!(new_value is string)
                    || !double.TryParse(new_value as string, out res)
                ) {
                    var.IsGood = false;
                    return;
                }
            }
            var.IsChanged = true;
            var.IsGood = true;
            var.Value = res;
        }

        /// <summary>
        /// Обработчик событий переключения радиокнопок
        /// </summary>
        private void FunctionChanged() {
            FunctionType? type = null;
            if(radioSh.Checked) {
                type = FunctionType.SH;
            } else if(radioSq.Checked) {
                type = FunctionType.SQR;
            } else if(radioE.Checked) {
                type = FunctionType.EXPONENT;
            }
            if(type == null) {
                throw new IndexOutOfRangeException();
            }
            ArgumentsStateChanged("f", type);
        }

        /// <summary>
        /// Обновляет значения изменившихся переменных, если все они корректны
        /// </summary>
        private void UpdateVariables() {
            bool canUpdateCalculatorState = true;
            canUpdateCalculatorState &= varX.IsGood;
            canUpdateCalculatorState &= varB.IsGood;
            canUpdateCalculatorState &= funcF.IsGood;
            if (!canUpdateCalculatorState) {
                return;
            }
            if (varX.IsChanged) {
                calculator.ChangeVariable("x", varX.Value);
            }
            if (varB.IsChanged) {
                calculator.ChangeVariable("b", varB.Value);
            }
            if (funcF.IsChanged) {
                switch(funcF.Value)
                {
                    case FunctionType.SH:
                        calculator.ChangeFunction("f", Math.Sinh);
                        break;
                    case FunctionType.EXPONENT:
                        calculator.ChangeFunction("f", Math.Exp);
                        break;
                    case FunctionType.SQR:
                        calculator.ChangeFunction("f", (x) => x * x);
                        break;
                }
            }
        }
    }
}
