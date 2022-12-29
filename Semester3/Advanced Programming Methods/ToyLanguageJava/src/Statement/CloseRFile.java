package Statement;

import ADT.PrgState;
import Exception.MyException;
import Expression.IExp;
import Type.StringType;
import Value.IValue;
import Value.StringValue;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.Buffer;

public class CloseRFile implements IStmt{
    IExp exp;

    public CloseRFile(IExp exp) {
        this.exp = exp;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        IValue result = exp.eval(state.getSymTable(),state.getHeap());
        if(!result.getType().equals(new StringType()))
            throw new MyException("The filename that you want to read is not a string");
        if(!state.getFileTable().isVarDef((StringValue)result))
            throw new MyException("The file was not opened!");
        try {
            BufferedReader br = state.getFileTable().lookUp((StringValue) result);
            br.close();
            state.getFileTable().remove((StringValue)result);
        }
        catch (IOException e) {
            throw new RuntimeException(e);
    }
    return null;
}

    @Override
    public IStmt deepCopy() {
        return new CloseRFile(exp.deepCopy());
    }

    @Override
    public String toString(){
        return "CloseRFile("+this.exp+")";
    }
}
