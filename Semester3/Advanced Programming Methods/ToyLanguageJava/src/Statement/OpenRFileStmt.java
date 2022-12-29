package Statement;

import ADT.PrgState;
import Expression.IExp;
import Exception.MyException;
import Type.StringType;
import Value.IValue;
import Value.StringValue;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.nio.Buffer;

public class OpenRFileStmt implements IStmt{
    private IExp exp;

    public OpenRFileStmt(IExp exp) {
        this.exp = exp;
    }

    public PrgState execute(PrgState prgState) throws MyException{
        IValue result = exp.eval(prgState.getSymTable(),prgState.getHeap());
        if(!result.getType().equals(new StringType()))
            throw new MyException("The name of the file must be a string");
        if(prgState.getFileTable().isVarDef((StringValue)result))
            throw new MyException("The file is already opened!");
        try
        {
         BufferedReader br = new BufferedReader(new FileReader(((StringValue)result).getVal()));
         prgState.getFileTable().put((StringValue)result,br);

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
            return null;
    }

    @Override
    public IStmt deepCopy() {
        return new OpenRFileStmt(exp.deepCopy());
    }

    @Override
    public String toString(){
        return "Open file("+exp+")";}


}
