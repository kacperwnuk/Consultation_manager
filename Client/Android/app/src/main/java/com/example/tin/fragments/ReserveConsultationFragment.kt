package com.example.tin.fragments


import android.os.AsyncTask
import android.os.Bundle
import android.os.Handler
import android.support.v4.app.Fragment
import android.support.v4.widget.SwipeRefreshLayout
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import com.example.tin.R
import com.example.tin.data.DataService
import com.example.tin.data.entity.ConsultationInfo
import com.example.tin.data.entity.enums.ConsultationStatus
import com.example.tin.recyler_adapters.FreeConsultationsRecyclerAdapter
import com.example.tin.recyler_adapters.TextRecyclerAdapter
import kotlinx.android.synthetic.main.fragment_reserve_consultation.*
import kotlinx.android.synthetic.main.fragment_reserve_consultation.view.*
import java.util.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val DATE = "date"

/**
 * A simple [Fragment] subclass.
 * Use the [ReserveConsultationFragment.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class ReserveConsultationFragment : Fragment(), FreeConsultationsRecyclerAdapter.ActionListener,
    SwipeRefreshLayout.OnRefreshListener, DataService.ConsultationsListener {

    private val handler = Handler()

    override fun onReservationSuccess() {
        handler.post {
            Toast.makeText(context, "Udało się zarezerwować konsultację", Toast.LENGTH_LONG).show()
            update()
        }
    }

    override fun onReservationFailure() {
        handler.post {
            Toast.makeText(context, "Nie udało się zarezerwować konsultacji", Toast.LENGTH_LONG).show()
            update()
        }
    }

    override fun updateFreeConsultations(consultations: List<ConsultationInfo>) {
        if (consultations.any { it.consultationStatus == ConsultationStatus.FREE }) {
            handler.post {
                updateView(
                    FreeConsultationsRecyclerAdapter(
                        consultations.filter {it.consultationStatus == ConsultationStatus.FREE }.sortedWith(
                            compareBy { it.consultationDateStart }
                        ), this
                    )
                )
            }
        } else {
            handler.post {
                updateView(
                    TextRecyclerAdapter(context!!.getString(R.string.no_consultations_found_message))
                )
            }
        }
    }

    override fun onRefresh() {
        update()
    }

    private var date: Long = Date().time

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        DataService.setConsultationsListener(this)
        arguments?.let {
            date = it.getLong(DATE)
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_reserve_consultation, container, false)
        view.swipe_container.setOnRefreshListener(this)
        update()
        return view
    }

    override fun addBefore(day: String, consultationDateEnd: String) {
        (context as ActionListener).addBefore(day, consultationDateEnd)
    }

    override fun addAfter(day: String, consultationDateStart: String) {
        (context as ActionListener).addAfter(day, consultationDateStart)
    }

    override fun reserve(id: String) {
        (context as ActionListener).reserve(id)
    }

    interface ActionListener {
        fun addBefore(day: String, endTime: String)

        fun addAfter(day: String, startTime: String)

        fun reserve(id: String)
    }

    fun update() {
        MyAsyncTask(date).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, null)
    }

    fun updateView(result: RecyclerView.Adapter<RecyclerView.ViewHolder>) {
        view!!.recyclerView.apply {
            setHasFixedSize(true)
            adapter = result
            layoutManager = LinearLayoutManager(context)
        }
        swipe_container.isRefreshing = false
    }

    private class MyAsyncTask internal constructor(val date: Long) :
        AsyncTask<Void, Void, Void>() {


        override fun doInBackground(vararg params: Void): Void? {
            val dataService = DataService
            dataService.getFreeConsultations(date)
            return null
        }

        override fun onPostExecute(void: Void?) {
        }
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param date Parameter 1.
         * @return A new instance of fragment reserve_consultation.
         */
        @JvmStatic
        fun newInstance(date: Long, param2: String) =
            ReserveConsultationFragment().apply {
                arguments = Bundle().apply {
                    putLong(DATE, date)
                }
            }
    }
}
