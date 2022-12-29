package Value;

import Type.IType;
import Type.IntType;
import Type.RefType;

public class RefValue implements IValue{
    int adress;
    IType locationType;
    @Override
    public IType getType() {
        return new RefType(locationType);
    }

    public IType getLocationType(){
        return locationType;

    }

    public int getAdress(){
        return this.adress;
    }



    public RefValue(int adress,IType locationType){
        this.adress = adress;
        this.locationType = locationType;
    }

    @Override
    public IValue deepCopy() {
        return new RefValue(adress,locationType);
    }

    @Override
    public String toString(){
        return "("+this.adress+","+locationType+")";
    }
}
