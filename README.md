# Calculator

![](C:\Users\Abdelrhman\Desktop\Calculator connection.PNG)

# Description

This calculator is used to evaluate simple math operation like add, subtract, multiplication and division

**This calculator support the following:**

- More than two operations.
- Negative numbers.
- Float numbers.
- Calculate according to precedence of operators.

# Code algorithm

1) Insert the math expression to the `MathExpressionArr`
2) Check the error : There are two types of error
   1) **Syntax error** : if the expression has a syntax error
   2) **Math error** : If the expression has number divided by zero

3. Check the negative numbers and convert the specified number to negative and convert negative sign to 32761.

4. Get the result : **By converting expression from infix to postfix**

   1. Check the `MathExpressionArr` elements 

      1. if the scanned element is **operator** 

         1. **Operator stack** is empty --> insert the scanned operator to `OperatorStack`
         2. if the scanned element has a **higher priority** than ``OperatorStack.top()`` --> insert the scanned operator to `operatorStack`
         3. if the scanned element has a **lower priority** than ``OperatorStack.top()`` :
            1. `SecondOperand`  = `OpeandStack.pop()`
            2. `FirstOperand` = `OperandStack.pop()`
            3. `Operator` = `OperatorStack.pop()`
            4. Evaluate the expression `Calculator_Evaluate(FirstOperand,Operator,SecondOperand,&Result);`
            5. `OperandStack.push(Result)`
            6. check for `OperandStack.size()` :
               1. **size > 1** --> Repeat from step 3.1
               2. **Size <= 1** --> Push current variable

          	2. if the scanned element is **operand**
               	1. push the operand to `OperandStack`

5. **Get the final result**
   1. `SecondOperand`  = `OpeandStack.pop()`
   2. `FirstOperand` = `OperandStack.pop()`
   3. `Operator` = `OperatorStack.pop()`
   4. Evaluate the expression `Calculator_Evaluate(FirstOperand,Operator,SecondOperand,&Result);`
   5. `OperandStack.push(Result)`
   6. check for `OperatorStack`:
      1. `OperatorStack.Size()`> 0 --> Repeat 5.1
      2. `OperatorStack.Size()`= 0 --> Print the result
