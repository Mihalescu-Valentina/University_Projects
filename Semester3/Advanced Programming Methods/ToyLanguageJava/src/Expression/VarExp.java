package Expression;

import ADT.IHeap;
import ADT.MyIDictionary;
import Value.IValue;
import Exception.MyException;

public class VarExp implements IExp {
    String id;

    public VarExp(String id) {
        this.id = id;
    }

    public IValue eval(MyIDictionary<String, IValue> tbl, IHeap<Integer,IValue> hp) throws MyException {
        return tbl.lookUp(id);
    }

    @Override
    public IExp deepCopy() {
        return new VarExp(new String(id));
    }

    @Override
    public String toString(){
        return id.toString();
    }
}
