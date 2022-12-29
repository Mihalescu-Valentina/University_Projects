package ADT;

import Value.IValue;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyDictionary<K, V> implements MyIDictionary<K, V> {

    private HashMap<K, V> map;


    public MyDictionary() {
        map = new HashMap<K, V>();
    }


    @Override
    public void put(K key, V value) {
        map.put(key, value);
    }

    @Override
    public boolean isVarDef(K key) {
        return map.containsKey(key);
    }

    @Override
    public void update(K key, V value) {
        map.put(key, value);
    }


    @Override
    public V lookUp(K key) {
        return map.get(key);
    }

    @Override
    public String toString() {
        return map.toString();
    }

    @Override
    public HashMap<K, V> getContent() {
        return this.map;
    }

    @Override
    public void setContent(HashMap<K, V> map2) {
        this.map = map2;
    }





}
