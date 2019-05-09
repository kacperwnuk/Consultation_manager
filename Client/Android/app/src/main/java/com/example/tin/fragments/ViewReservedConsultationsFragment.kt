package com.example.tin.fragments

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
import com.example.tin.MainActivity
import com.example.tin.recyler_adapters.MyBookedConsultationsRecyclerAdapter
import com.example.tin.recyler_adapters.NoConsultationsRecyclerAdapter
import com.example.tin.R
import com.example.tin.data.DataService
import kotlinx.android.synthetic.main.fragment_view_reserved_consultations.*
import kotlinx.android.synthetic.main.fragment_view_reserved_consultations.view.*
import java.lang.ref.WeakReference


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val CONSULTATIONS = "consultations"

/**
 * A simple [Fragment] subclass.
 * Activities that contain this fragment must implement the
 * [ViewReservedConsultationsFragment.ActionListener] interface
 * to handle interaction events.
 * Use the [ViewReservedConsultationsFragment.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class ViewReservedConsultationsFragment : Fragment(),
    MyBookedConsultationsRecyclerAdapter.ActionListener, SwipeRefreshLayout.OnRefreshListener {

    override fun cancelConsultation(id: String) {
        (context as ActionListener).cancelConsultation(id)
    }

    override fun onRefresh() {
        update()
    }

    interface ActionListener {
        fun cancelConsultation(id: String)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_view_reserved_consultations, container, false)
        view.swipe_container.setOnRefreshListener(this)
        update()
        return view
    }

    fun update() {
        MyAsyncTask(context!!, this)
            .executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, null)
    }

    private class MyAsyncTask internal constructor(context: Context, actionListener: ViewReservedConsultationsFragment): AsyncTask<Void, Void, RecyclerView.Adapter<RecyclerView.ViewHolder>>() {

        private val context: WeakReference<Context> = WeakReference(context)
        private val actionListener: WeakReference<ViewReservedConsultationsFragment> = WeakReference(actionListener)

        override fun doInBackground(vararg params: Void): RecyclerView.Adapter<RecyclerView.ViewHolder> {
            val dataService = DataService
            val consultations = dataService.getReservedConsultations((context.get() as MainActivity).credential!!.id)
            return if (consultations.isNotEmpty()) {
                MyBookedConsultationsRecyclerAdapter(
                    consultations.sortedWith(
                        compareBy(
                            { it.day },
                            { it.startTime })
                    ), actionListener.get()!!
                )
            } else {
                NoConsultationsRecyclerAdapter()
            }
        }

        override fun onPostExecute(result: RecyclerView.Adapter<RecyclerView.ViewHolder>) {
            actionListener.get()!!.updateView(result)
        }
    }

    fun updateView(result: RecyclerView.Adapter<RecyclerView.ViewHolder>) {
        view!!.recyclerView.apply {
            setHasFixedSize(true)
            adapter = result
            layoutManager = LinearLayoutManager(context)
        }
        swipe_container.isRefreshing = false
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @return A new instance of fragment ViewReservedConsultationsFragment.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance() = ViewReservedConsultationsFragment()
    }
}
