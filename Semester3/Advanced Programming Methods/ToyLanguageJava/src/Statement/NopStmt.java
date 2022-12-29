package Statement;

import ADT.PrgState;

import Exception.MyException;

public class NopStmt implements IStmt {
    public NopStmt() {
    }

    public PrgState execute(PrgState state) throws MyException{
        return null;
    };
    public String toString(){return new String();};

    public IStmt deepCopy(){ return new NopStmt();};

}
