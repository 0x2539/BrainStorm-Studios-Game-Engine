package brainstorm.super_ultra_mega_app.app;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;


public class Second_activity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
	    this.getActionBar().setDisplayShowTitleEnabled(false);
	    this.getActionBar().setDisplayShowHomeEnabled(false);
	    setContentView(R.layout.activity_second_activity);

	    Control_helper controls = new Control_helper(this, this.getWindow());

	    Intent _current_intent = getIntent();

	    controls.add_text_edit_to_layout(R.id.linearLayoutSecondScreen, new EditText(this), _current_intent.getStringExtra("string1"));
	}


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.second_activity, menu);
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
