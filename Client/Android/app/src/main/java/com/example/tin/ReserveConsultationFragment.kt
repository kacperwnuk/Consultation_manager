package com.example.tin


import android.content.Context
import android.os.AsyncTask
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v4.widget.SwipeRefreshLayout
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.example.tin.data.Consultation
import com.example.tin.data.ConsultationType
import com.example.tin.data.DataService
import kotlinx.android.synthetic.main.fragment_reserve_consultation.*
import kotlinx.android.synthetic.main.fragment_reserve_consultation.view.*
import java.lang.ref.WeakReference
import java.util.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val DATE = "date"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 * Use the [ReserveConsultationFragment.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class ReserveConsultationFragment : Fragment(), FreeConsultationsRecyclerAdapter.ActionListener,
    SwipeRefreshLayout.OnRefreshListener, DataService.ConsultationsListener {

    override fun updateFreeConsultations(consultations: List<Consultation>) {
        updateView(
            FreeConsultationsRecyclerAdapter(
                consultations.sortedWith(
                    compareBy({ it.day },
                        { it.startTime })
                ), this
            )
        )
    }

    override fun onRefresh() {
        update()
    }

    // TODO: Rename and change types of parameters
    private var date: Long = Date().time
    private var param2: String? = null

    private lateinit var recyclerAdapter: RecyclerView.Adapter<RecyclerView.ViewHolder>

    private val consultations = listOf(
        Consultation("3", "Dr. inż. Gawkowski", "12.00", "12.15", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("4", "Dr. inż. Gawkowski", "12.15", "12.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("5", "Dr. inż. Gawkowski", "12.30", "12.45", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("6", "Dr. inż. Gawkowski", "12.45", "13.00", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("7", "Dr. inż. Gawkowski", "16.45", "17.15", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("8", "Dr. inż. Gawkowski", "17.15", "17.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("9", "Dr. inż. Gawkowski", "12.00", "12.15", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("10", "Dr. inż. Gawkowski", "12.15", "12.30", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("11", "Dr. inż. Gawkowski", "12.30", "12.45", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("12", "Dr. inż. Gawkowski", "12.45", "13.00", "22.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("13", "Dr. inż. Gawkowski", "13.00", "13.15", "22.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("14", "Dr. inż. Gawkowski", "13.15", "13.30", "22.03.2019", ConsultationType.LECTURER_SUGGESTED)
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        DataService.setConsultationsListener(this)
        arguments?.let {
            date = it.getLong(DATE)
            param2 = it.getString(ARG_PARAM2)
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

    override fun addBefore(day: String, endTime: String) {
        (context as ActionListener).addBefore(day, endTime)
    }

    override fun addAfter(day: String, startTime: String) {
        (context as ActionListener).addAfter(day, startTime)
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
        MyAsyncTask(context!!, this, date).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, null)
    }

    fun updateView(result: FreeConsultationsRecyclerAdapter) {
        view!!.recyclerView.apply {
            setHasFixedSize(true)
            adapter = result
            layoutManager = LinearLayoutManager(context)
        }
        swipe_container.isRefreshing = false
    }

    private class MyAsyncTask internal constructor(context: Context, actionListener: ReserveConsultationFragment, val date: Long) :
        AsyncTask<Void, Void, FreeConsultationsRecyclerAdapter>() {

        private val context: WeakReference<Context> = WeakReference(context)
        private val actionListener: WeakReference<ReserveConsultationFragment> = WeakReference(actionListener)

        override fun doInBackground(vararg params: Void): FreeConsultationsRecyclerAdapter {
            val dataService = DataService
            val consultations = dataService.getFreeConsultations(date)
            return FreeConsultationsRecyclerAdapter(
                consultations.sortedWith(
                    compareBy({ it.day },
                        { it.startTime })
                ), actionListener.get()!!
            )
        }

        override fun onPostExecute(result: FreeConsultationsRecyclerAdapter) {
//            actionListener.get()!!.updateView(result)
        }
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param param1 Parameter 1.
         * @param param2 Parameter 2.
         * @return A new instance of fragment reserve_consultation.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance(date: Long, param2: String) =
            ReserveConsultationFragment().apply {
                arguments = Bundle().apply {
                    putLong(DATE, date)
                    putString(ARG_PARAM2, param2)
                }
            }
    }
}
