package Expression;


import ADT.IHeap;
import ADT.MyIDictionary;
import ADT.PrgState;
import Statement.IStmt;
import Value.IValue;
import Value.RefValue;


import ADT.IHeap;
import ADT.MyIDictionary;
import ADT.PrgState;
import Exception.MyException;
import Expression.IExp;
import Value.IValue;
import Value.RefValue;

public class rHExp implements IExp {
        IExp expression;

        public rHExp(IExp exp) {
            this.expression = exp;
        }

        @Override
        public IValue eval(MyIDictionary<String, IValue> tbl, IHeap<Integer,IValue>hp) throws MyException {
            if(!(expression.eval(tbl,hp) instanceof RefValue))
                throw new MyException("The value is not a reference value!");
            int addressRefValue = ((RefValue) expression.eval(tbl,hp)).getAdress();
            if(!(hp.isVarDef(addressRefValue)))
                throw new MyException("This adress is not on the heap!");
            return hp.lookUp(addressRefValue);

        }

        @Override
        public IExp deepCopy() {
            return new rHExp(expression);
        }

        @Override
        public String toString(){
            return "rH("+expression+")";
        };

    }



