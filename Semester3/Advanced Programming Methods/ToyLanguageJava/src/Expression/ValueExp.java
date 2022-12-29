package Expression;

import ADT.IHeap;
import ADT.MyIDictionary;
import Type.BoolType;
import Type.IntType;
import Type.StringType;
import Value.BoolValue;
import Value.IValue;
import Exception.MyException;
import Value.IntValue;

public class ValueExp implements IExp{
    IValue val;

    public ValueExp(IValue val) {
        this.val = val;
    }

    @Override
    public String toString() {
        return val.toString();
    }

    @Override
    public IValue eval(MyIDictionary<String,IValue> tbl, IHeap<Integer,IValue>hp) throws MyException{
//        if(val.getType().equals(new IntType()) || val.getType().equals(new StringType()))
//           return val;
//        else if(val.getType().equals(new BoolType())){
//            BoolValue b= (BoolValue) val;
//            if(b.getVal())
//                return new BoolValue(true);
//            else
//                return new BoolValue(false);
//
//
//        }
//        else throw new MyException("The value is not recognised by the interpreter!");
        return val;

    }

    @Override
    public IExp deepCopy(){
        return new ValueExp(val.deepCopy()) ;
    }
}
