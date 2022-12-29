package Statement;

import ADT.PrgState;
import Exception.MyException;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;
    String toString();

    IStmt deepCopy();

}
