package Statement;

import ADT.MyIDictionary;
import ADT.MyIStack;
import ADT.PrgState;
import Exception.MyException;
import Type.IType;
import Value.IValue;

public class VarDeclStmt implements IStmt{

    String name;
    IType type;

    public VarDeclStmt(String name, IType type) {
        this.name = name;
        this.type = type;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getExeStack();
        MyIDictionary<String, IValue> tbl = state.getSymTable();
        if(tbl.isVarDef(name))
            throw new MyException("The variable" +name +" is already defined");
        else
        {
            tbl.put(name,type.defaultValue());

        }
        return null;

    }

    @Override
    public String toString(){
        return type+" "+name;
    }

    @Override
    public IStmt deepCopy() {
        return new VarDeclStmt(new String(name),type.deepCopy());
    }




}
