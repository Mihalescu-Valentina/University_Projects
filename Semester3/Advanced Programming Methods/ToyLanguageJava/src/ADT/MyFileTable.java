package ADT;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyFileTable<K,V> implements MyIFileTable<K,V>{
    private ConcurrentHashMap<K,V> ftbl;

    @Override
    public String toString(){
        return ftbl.toString();
    }


    public MyFileTable(){
        ftbl = new ConcurrentHashMap<K,V>();
    }

    @Override
    public void put(K key, V value){
        ftbl.put(key,value);
    }

    @Override
    public boolean isVarDef(K key){
        return ftbl.containsKey(key);
    }

    @Override
    public void update(K key,V value){
        ftbl.put(key,value);
    }

    @Override
    public void remove(K key) {
        ftbl.remove(key);
    }


    @Override
    public V lookUp(K key){
        return ftbl.get(key);
    }



}
