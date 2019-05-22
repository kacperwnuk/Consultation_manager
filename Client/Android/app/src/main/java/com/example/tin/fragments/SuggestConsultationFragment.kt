package com.example.tin.fragments

import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.annotation.SuppressLint
import android.annotation.TargetApi
import android.app.DatePickerDialog
import android.app.TimePickerDialog
import android.os.AsyncTask
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.support.v4.app.Fragment
import android.text.SpannableStringBuilder
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import com.example.tin.MainActivity
import com.example.tin.R
import com.example.tin.data.DataService
import com.example.tin.dto.request.NewConsultationRequest
import kotlinx.android.synthetic.main.fragment_suggest_consultation.*
import kotlinx.android.synthetic.main.fragment_suggest_consultation.view.*
import java.text.SimpleDateFormat
import java.util.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val START_TIME = "start_time"
private const val END_TIME = "end_time"
private const val DATE = "date"
private const val LECTURER = "lecturer"

/**
 * A simple [Fragment] subclass.
 * Activities that contain this fragment must implement the
 * [SuggestConsultationFragment.ActionListener] interface
 * to handle interaction events.
 * Use the [SuggestConsultationFragment.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class SuggestConsultationFragment : Fragment(), DataService.SuggestConsultationListener {

    private val handler = Handler()

    override fun onSuggestFailure() {
        handler.post {
            Toast.makeText(context, "Something went wrong", Toast.LENGTH_LONG).show()
        }
    }

    override fun onSuggestSuccess() {
        handler.post {
            Toast.makeText(context, "Consultation added successfully", Toast.LENGTH_LONG).show()
        }
    }

    interface ActionListener {
        fun suggestedConsultation()
    }

    private var mConsultationSuggestTask: ConsultationSuggestTask? = null
    private var startTime: String? = null
    private var endTime: String? = null
    private var date: String? = null
    private var lecturer: String? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        arguments?.let {
            startTime = it.getString(START_TIME)
            endTime = it.getString(END_TIME)
            date = it.getString(DATE)
            lecturer = it.getString(LECTURER)
        }
        DataService.setSuggestConsultationListener(this)
    }

    @SuppressLint("SetTextI18n")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_suggest_consultation, container, false)
        var startTimeHour = 12
        var endTimeHour = 12
        var startTimeMinute = 0
        var endTimeMinute = 0
        if (startTime != null) {
            startTimeHour = startTime!!.split(":")[0].toInt()
            startTimeMinute = startTime!!.split(":")[1].toInt()
            if (startTimeMinute >= 45) {
                endTimeMinute = startTimeMinute - 45
                endTimeHour = if (startTimeHour == 23) {
                    0
                } else {
                    startTimeHour + 1
                }
            } else {
                endTimeHour = startTimeHour
                endTimeMinute = startTimeMinute + 15
            }
            endTime = "$endTimeHour:${String.format("%02d", endTimeMinute)}"
            disableView(view.start_time)
        } else if (endTime != null) {
            endTimeHour = endTime!!.split(":")[0].toInt()
            endTimeMinute = endTime!!.split(":")[1].toInt()
            if (endTimeMinute < 15) {
                startTimeMinute = endTimeMinute + 45
                startTimeHour = if (endTimeHour == 0) {
                    23
                } else {
                    endTimeHour - 1
                }
            } else {
                startTimeHour = endTimeHour
                startTimeMinute = endTimeMinute - 15
            }
            startTime = "$startTimeHour:${String.format("%02d", startTimeMinute)}"
            disableView(view.end_time)
        } else {
            startTime = "13:00"
            endTime = "14:00"
        }
        if (date != null) {
            view.date.text = SpannableStringBuilder(date)
            disableView(view.date)
        } else {
            date = SimpleDateFormat("yyyy-MM-dd", Locale.US).format(Calendar.getInstance().time)
            view.date.text = SpannableStringBuilder(date)
        }
        view.end_time.text = SpannableStringBuilder("$endTimeHour:${String.format("%02d", endTimeMinute)}")
        view.start_time.text = SpannableStringBuilder("$startTimeHour:${String.format("%02d", startTimeMinute)}")
        view.start_time.setOnClickListener {
            val timePicker =
                TimePickerDialog(context, TimePickerDialog.OnTimeSetListener { _, selectedHour, selectedMinute ->
                    startTime = "$selectedHour:${String.format("%02d", selectedMinute)}"
                    view.start_time.text = SpannableStringBuilder(startTime)
                }, startTimeHour, startTimeMinute, true)
            timePicker.show()
        }
        view.end_time.setOnClickListener {
            val timePicker =
                TimePickerDialog(context, TimePickerDialog.OnTimeSetListener { _, selectedHour, selectedMinute ->
                    endTime = "$selectedHour:${String.format("%02d", selectedMinute)}"
                    view.end_time.text = SpannableStringBuilder(endTime)
                }, endTimeHour, endTimeMinute, true)
            timePicker.show()
        }
        view.suggest_button.setOnClickListener {
            showProgress(true)
            val simpleDateFormat = SimpleDateFormat("yyyy-MM-dd hh:mm", Locale.US)
            val startDate = simpleDateFormat.parse("$date $startTime")
            val endTime = simpleDateFormat.parse("$date $endTime")
            mConsultationSuggestTask = ConsultationSuggestTask(
                NewConsultationRequest(
                    (context as MainActivity).credential!!.id,
                    startDate.time,
                    endTime.time,
                    ""
                )
            )
            mConsultationSuggestTask!!.execute(null as Void?)
        }
        view.date.setOnClickListener {
            val currentDate = Calendar.getInstance()
            val datePicker = DatePickerDialog(
                context,
                DatePickerDialog.OnDateSetListener { _, year, month, dayOfMonth ->
                    date = "$year-${String.format("%02d", month + 1)}-${String.format("%02d", dayOfMonth)}"
                    view.date.text = SpannableStringBuilder(date)
                },
                currentDate.get(Calendar.YEAR),
                currentDate.get(Calendar.MONTH),
                currentDate.get(Calendar.DAY_OF_MONTH)
            )
            datePicker.show()
        }
        return view
    }

    private fun disableView(view: View) {
        view.isClickable = false
        view.isEnabled = false
        view.isFocusable = false
    }

    /**
     * Represents an asynchronous login/registration task used to authenticate
     * the user.
     */
    inner class ConsultationSuggestTask internal constructor(private val newConsultationRequest: NewConsultationRequest) :
        AsyncTask<Void, Void, Boolean>() {


        override fun doInBackground(vararg params: Void): Boolean? {
            val dataService = DataService
            dataService.newConsultation(newConsultationRequest)


            return true
        }

        override fun onPostExecute(success: Boolean?) {
            mConsultationSuggestTask = null
            showProgress(false)

            if (success!!) {

            } else {
            }
        }

        override fun onCancelled() {
            mConsultationSuggestTask = null
            showProgress(false)
        }
    }

    /**
     * Shows the progress UI and hides the login form.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private fun showProgress(show: Boolean) {
        // On Honeycomb MR2 we have the ViewPropertyAnimator APIs, which allow
        // for very easy animations. If available, use these APIs to fade-in
        // the progress spinner.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            val shortAnimTime = resources.getInteger(android.R.integer.config_shortAnimTime).toLong()

            add_consultation_form.visibility = if (show) View.GONE else View.VISIBLE
            add_consultation_form.animate()
                .setDuration(shortAnimTime)
                .alpha((if (show) 0 else 1).toFloat())
                .setListener(object : AnimatorListenerAdapter() {
                    override fun onAnimationEnd(animation: Animator) {
                        add_consultation_form.visibility = if (show) View.GONE else View.VISIBLE
                    }
                })

            add_progress.visibility = if (show) View.VISIBLE else View.GONE
            add_progress.animate()
                .setDuration(shortAnimTime)
                .alpha((if (show) 1 else 0).toFloat())
                .setListener(object : AnimatorListenerAdapter() {
                    override fun onAnimationEnd(animation: Animator) {
                        add_progress.visibility = if (show) View.VISIBLE else View.GONE
                    }
                })
        } else {
            // The ViewPropertyAnimator APIs are not available, so simply show
            // and hide the relevant UI components.
            add_progress.visibility = if (show) View.VISIBLE else View.GONE
            add_consultation_form.visibility = if (show) View.GONE else View.VISIBLE
        }
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param startTime Parameter 1.
         * @param end_time Parameter 2.
         * @return A new instance of fragment SuggestConsultationFragment.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance(startTime: String?, end_time: String?, date: String?, lecturer: String?) =
            SuggestConsultationFragment().apply {
                arguments = Bundle().apply {
                    putString(START_TIME, startTime)
                    putString(END_TIME, end_time)
                    putString(DATE, date)
                    putString(LECTURER, lecturer)
                }
            }
    }
}
