package Statement;

import ADT.MyIStack;
import ADT.PrgState;
import Exception.MyException;

public class CompStmt implements IStmt{
    IStmt first;
    IStmt second;

    public CompStmt(IStmt first, IStmt second) {
        this.first = first;
        this.second = second;
    }


    @Override
    public String toString(){
        return "("+first.toString() + ";" + second.toString()+")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getExeStack();
        stack.push(second);
        stack.push(first);
        return null;

    }
    @Override
    public IStmt deepCopy(){
        return new CompStmt(first.deepCopy(),second.deepCopy());
    }


}
