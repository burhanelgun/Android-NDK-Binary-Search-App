package com.example.native2;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    ArrayList<Integer> arr;
    TextView arrTextView;
    EditText valEditText;
    Button addButton;
    EditText findEditText;
    Button findButton;
    TextView findTextView;
    TextView indexTextView;



    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        arr=new ArrayList();
        arrTextView = findViewById(R.id.arrTextView);
        valEditText=findViewById(R.id.valEditText);
        findEditText=findViewById(R.id.findEditText);
        findTextView=findViewById(R.id.findTextView);
        indexTextView=findViewById(R.id.indexTextView);



        findButton=findViewById(R.id.findButton);
        findButton.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                if(findEditText.getText().toString().length()!=0){
                    arr=primitiveArrayToArrayList(insertionSort(arrayListToPrimitiveArray(arr)));
                    arrTextView.setText("Array: "+String.valueOf(getStringOfArrayList(arr)));
                    indexTextView.setText("Index: "+ binarySearch(arrayListToPrimitiveArray(arr),Integer.parseInt(findEditText.getText().toString())));
                }

            }
        });

        addButton= findViewById(R.id.addButton);
        addButton.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {

                if(valEditText.getText().toString().length()!=0 && !arr.contains(Integer.parseInt(valEditText.getText().toString()))){
                    arr.add(Integer.parseInt(valEditText.getText().toString()));
                    arrTextView.setText("Array: "+String.valueOf(getStringOfArrayList(arr)));
                }
                valEditText.getText().clear();


            }
        });


    }


    public native int[] insertionSort(int[] arr);

    public native int binarySearch(int[] arr,int val);


    private String getStringOfArrayList(ArrayList<Integer> arr){
        StringBuilder stringBuilder=new StringBuilder();
        stringBuilder.append(" { ");
        for (int i=0;i<arr.size();i++){
            stringBuilder.append(String.valueOf(arr.get(i)));
            if(i!=arr.size()-1)
                stringBuilder.append(" , ");
        }
        stringBuilder.append(" } ");
        return stringBuilder.toString();
    }

    private int[] arrayListToPrimitiveArray(ArrayList<Integer> arrList)
    {
        int[] intArray = new int[arrList.size()];

        for(int i=0;i<arrList.size();i++){
            intArray[i]=arrList.get(i);
        }

        return intArray;
    }
    private ArrayList<Integer> primitiveArrayToArrayList(int[] arr) {
        ArrayList<Integer> arrayList=new ArrayList<>();

        for(int i=0;i<arr.length;i++){
            arrayList.add(arr[i]);
        }

        return arrayList;
    }

}
