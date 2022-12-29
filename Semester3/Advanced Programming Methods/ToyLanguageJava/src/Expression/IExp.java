package Expression;

import ADT.IHeap;
import ADT.MyIDictionary;
import Value.IValue;
import Exception.MyException;

public interface IExp {
    IValue eval(MyIDictionary<String,IValue> tbl, IHeap<Integer,IValue>hp) throws MyException  ;

    IExp deepCopy();

    String toString();
}
