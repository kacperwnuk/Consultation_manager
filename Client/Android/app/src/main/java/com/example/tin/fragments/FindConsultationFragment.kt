package com.example.tin.fragments

import android.content.Context
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.example.tin.R
import kotlinx.android.synthetic.main.fragment_find_consultation.view.*
import java.util.*

/**
 * A simple [Fragment] subclass.
 * Activities that contain this fragment must implement the
 * [FindConsultationFragment.OnSearchListener] interface
 * to handle interaction events.
 * Use the [FindConsultationFragment.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class FindConsultationFragment : Fragment() {

    private var listener: OnSearchListener? = null
    private var selectedEpochTime: Long = Date().time

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_find_consultation, container, false)
        view.calendar_view.setOnDateChangeListener { view, year, month, day ->
            val calendar = Calendar.getInstance()
            calendar.set(Calendar.YEAR, year)
            calendar.set(Calendar.MONTH, month)
            calendar.set(Calendar.DATE, day)
            calendar.set(Calendar.HOUR_OF_DAY, 0)
            val date = calendar.time
            selectedEpochTime = date.time
        }
        view.search_button.setOnClickListener {
            listener!!.onSearchConsultation(selectedEpochTime)
        }
        return view
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        if (context is OnSearchListener) {
            listener = context
        } else {
            throw RuntimeException(context.toString() + " must implement OnSearchListener")
        }
    }

    override fun onDetach() {
        super.onDetach()
        listener = null
    }

    /**
     * This interface must be implemented by activities that contain this
     * fragment to allow an interaction in this fragment to be communicated
     * to the activity and potentially other fragments contained in that
     * activity.
     *
     */
    interface OnSearchListener {
        fun onSearchConsultation(date: Long)
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @return A new instance of fragment FindConsultationFragment.
         */
        @JvmStatic
        fun newInstance() = FindConsultationFragment()
    }
}
