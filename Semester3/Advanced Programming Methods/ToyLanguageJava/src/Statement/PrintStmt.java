package Statement;

import ADT.MyIDictionary;
import ADT.MyIList;
import ADT.MyIStack;
import ADT.PrgState;
import Expression.IExp;
import Exception.MyException;
import Value.IValue;

public class PrintStmt implements IStmt{
    IExp exp;

    public PrintStmt(IExp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getExeStack();
        MyIList<IValue>out = state.getOut();
        out.add(exp.eval(state.getSymTable(),state.getHeap()));
        return null;

    }

    @Override
    public String toString(){
        return "print(" +exp.toString()+")";
    }

    @Override
    public IStmt deepCopy(){
        return new PrintStmt(exp.deepCopy());
    }
}
