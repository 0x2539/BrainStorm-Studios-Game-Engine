package brainstorm.super_ultra_mega_app.app;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Created by Alexandru on 3/27/14.
 */
public class Control_helper extends Activity
{
	Context _the_context;
	Window _the_current_window;

	Control_helper(Context _new_context, Window _new_window)
	{
		Log.i("control_helper", "context nou creat");
		_the_context = _new_context;
		_the_current_window = _new_window;
	}

	public void add_text_edit_to_layout(int _layout_id, EditText _current_text_edit, String _text_to_add)
	{
		LinearLayout _the_layout = (LinearLayout) _the_current_window.findViewById(_layout_id);

		if(_the_layout != null)
		{
			_current_text_edit = new EditText(_the_context);
			_current_text_edit.setText(_text_to_add);
			_the_layout.addView(_current_text_edit);
		}
		else
		{
			Toast.makeText(_the_context, "Eroare in add_text_edit_to_layout()", Toast.LENGTH_LONG).show();
			Log.e("control_helper", "Eroare in add_text_edit_to_layout()");
		}
	}

	public void add_text_view_to_layout(int _layout_id, TextView _current_text_view, String _text_to_add)
	{
		LinearLayout _the_layout = (LinearLayout) _the_current_window.findViewById(_layout_id);

		if(_the_layout != null)
		{
			_current_text_view = new TextView(_the_context);
			_current_text_view.setText(_text_to_add);
			_the_layout.addView(_current_text_view);
		}
		else
		{
			Toast.makeText(_the_context, "Eroare in add_text_view_to_layout()", Toast.LENGTH_LONG).show();
			Log.e("control_helper", "Eroare in add_text_view_to_layout()");
		}
	}

	public void add_button_to_layout(int _layout_id, Button _current_button, String _text_to_add)
	{
		LinearLayout _the_layout = (LinearLayout) _the_current_window.findViewById(_layout_id);
		if(_the_layout != null)
		{
			_current_button = new Button(_the_context);
			_current_button.setText(_text_to_add);
			_current_button.setOnClickListener(new View.OnClickListener()
			{
				public void onClick(View arg0)
				{
					//Starting a new Intent
					Intent nextScreen = new Intent(_the_context.getApplicationContext(), Second_activity.class);

					//Sending data to another Activity
					nextScreen.putExtra("string1", "valoarea stringului 1");
					nextScreen.putExtra("string2", "valoarea stringului 2");

					_the_context.startActivity(nextScreen);
				}
			});
			_the_layout.addView(_current_button);
		}
		else
		{
			Toast.makeText(_the_context, "Eroare in add_button_to_layout()", Toast.LENGTH_LONG).show();
			Log.e("control_helper", "Eroare in add_button_to_layout()");
		}
	}

	public void change_text_view_from_layout(int _text_view_id, String _text_to_change)
	{
		TextView _current_text_view = (TextView) _the_current_window.findViewById(_text_view_id);
		_current_text_view.setText(_text_to_change);
	}

	public void remove_text_view_from_layout(int _text_view_id)
	{
		TextView _current_text_view = (TextView) _the_current_window.findViewById(_text_view_id);
		ViewGroup _the_layout = (ViewGroup) _current_text_view.getParent();

		if(_the_layout != null && _current_text_view != null)
		{
			_the_layout.removeView(_current_text_view);
		}
		else
		{
			Toast.makeText(_the_context, "Eroare in remove_text_view_from_layout()", Toast.LENGTH_LONG).show();
			Log.e("control_helper", "Eroare in remove_text_view_from_layout()");
		}
	}

	public void replace_text_view_from_layout(int _current_layout_id, int _text_view_id, String _text_to_add)
	{
		remove_text_view_from_layout(_text_view_id);
		add_text_view_to_layout(_current_layout_id, new TextView(_the_context), _text_to_add);
	}

	public String read_file(String file_name)
	{
		FileInputStream fis = null;
		StringBuffer fileContent = new StringBuffer("");
		try
		{
			fis = _the_context.openFileInput(file_name);
			byte[] buffer = new byte[1024];

			while (fis.read(buffer) != -1)
			{
				fileContent.append(new String(buffer));
			}
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		return fileContent.toString();
	}
}
