package brainstorm.super_ultra_mega_app.app;

import android.annotation.TargetApi;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ResourceBundle;


public class MainActivity extends ActionBarActivity {

    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
	    super.onCreate(savedInstanceState);
	    this.getActionBar().setDisplayShowTitleEnabled(false);
	    this.getActionBar().setDisplayShowHomeEnabled(false);
	    setContentView(R.layout.layoutul_meu);
	    Toast.makeText(this, "a pornit main activity", Toast.LENGTH_LONG).show();

	    Control_helper controls = new Control_helper(this, this.getWindow());

	    String file = controls.read_file("test.txt");
	    String linii[] = file.split("\n");

	    controls.add_button_to_layout(R.id.linearLayout2, new Button(this), "textul meu pentru buton");
	    controls.add_text_view_to_layout(R.id.linearLayout2, new TextView(this), "textul meu pentru text view");
	    controls.change_text_view_from_layout(R.id.textView, "textul meu pentru primul text view");
	    controls.replace_text_view_from_layout(R.id.linearLayout2, R.id.textView, "textul noului text view");

	    for(int i = 0; i < linii.length; i++)
	    {

	    }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

}
