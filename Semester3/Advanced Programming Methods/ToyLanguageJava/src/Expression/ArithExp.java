package Expression;

import ADT.IHeap;
import ADT.MyIDictionary;
import Type.BoolType;
import Type.IType;
import Type.IntType;
import Value.IValue;
import Exception.MyException;
import Value.IntValue;

public class ArithExp implements IExp {
    IExp exp1;
    IExp exp2;

    int op;

    public ArithExp(IExp exp1, IExp exp2,int op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    public IValue eval(MyIDictionary<String, IValue> tbl, IHeap<Integer,IValue>hp) throws MyException {

        IValue v1,v2;
        v1= exp1.eval(tbl,hp);
        if (v1.getType().equals(new IntType())) {
            v2 = exp2.eval(tbl,hp);
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;
                int n1,n2;
                n1= i1.getVal();
                n2 = i2.getVal();
                switch(op){
                    case 1:
                        return new IntValue(n1+n2);
                    case 2:
                        return new IntValue(n1-n2);

                    case 3:
                        return new IntValue(n1*n2);

                    case 4:
                        if(n2==0) throw new MyException("division by zero");
                        else  return new IntValue(n1/n2);



                }

            }else
                throw new MyException("second operand is not an integer");
        }else
            throw new MyException("first operand is not an integer");
        return null;
    }

    /*public IType typecheck(MyIDictionary<String,IType>typeEnv)throws MyException {
        IType t1,t2;
        t1 = exp1.typecheck(typeEnv);
        t2 = exp2.typecheck(typeEnv);
        if(t1.equals(new BoolType())){
            if(t2.equals(new BoolType()))
                return new BoolType();
        }

        else
            throw new MyException("The types of the expressions from the logical expression do not match(are not bool)!");
        return null;

    }*/



    public IExp deepCopy(){
        return new ArithExp(exp1.deepCopy(),exp2.deepCopy(),op);
    }

    @Override
    public String toString(){
        if(op==1)
             return exp1.toString()+"+"+exp2.toString();
        else
            if(op==2)
                return exp1.toString()+"-"+exp2.toString();
        else
            if(op==3)
                return exp1.toString()+"*"+exp2.toString();
        else
            if(op==4)
                return exp1.toString()+"/"+exp2.toString();
        else {
                return "";
            }
    }

}
