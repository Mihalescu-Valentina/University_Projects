package Statement;

import ADT.IHeap;
import ADT.MyIDictionary;
import ADT.MyIStack;
import ADT.PrgState;
import Expression.IExp;
import Exception.MyException;
import Type.BoolType;
import Type.IType;
import Value.BoolValue;
import Value.IValue;
import Value.IntValue;

public class IfStmt implements IStmt {

    IExp exp;
    IStmt thenS;
    IStmt elseS;

    @Override
    public String toString() {
        return "(IF(" + exp.toString() + ") THEN(" + thenS.toString()
                + ")ELSE(" + elseS.toString() + "))";
    }

    public IfStmt(IExp e, IStmt t, IStmt el) {
        exp = e;
        thenS = t;
        elseS = el;
    }

    @Override
    public IStmt deepCopy() {
        return new IfStmt(exp.deepCopy(), thenS.deepCopy(), elseS.deepCopy());
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIStack<IStmt> stack = state.getExeStack();
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        IHeap<Integer,IValue>hp = state.getHeap();
        IValue cond = exp.eval(symTbl,hp);
        IType val = new BoolType();
        if (!cond.getType().equals(val)) {
            throw new MyException("conditional expr is not a boolean");
        } else if (cond.getType().equals(val)) {
            BoolValue b = (BoolValue) cond;
           if (b.getVal()) {

                stack.push(thenS);
            } else
                stack.push(elseS);

        }

        return null;
    }


}
