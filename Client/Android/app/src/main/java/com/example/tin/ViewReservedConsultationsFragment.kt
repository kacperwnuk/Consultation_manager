package com.example.tin

import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.example.tin.data.Consultation
import com.example.tin.data.ConsultationType
import kotlinx.android.synthetic.main.fragment_reserve_consultation.view.*


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
class ViewReservedConsultationsFragment : Fragment() {

    interface ActionListener {
        fun cancelConsultation()
    }

    private lateinit var recyclerAdapter: RecyclerView.Adapter<RecyclerView.ViewHolder>

    private val consultations = listOf(
        Consultation("Dr. inż. Kozdrowski", "12.00", "12.15", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("Dr. inż. Kozdrowski", "12.15", "12.30", "21.03.2019", ConsultationType.LECTURER_SUGGESTED)
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        recyclerAdapter = MyBookedConsultationsRecyclerAdapter(consultations.sortedWith (compareBy ({it.day}, {it.startTime})))
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_view_reserved_consultations, container, false)
        view.recyclerView.apply {
            setHasFixedSize(true)
            adapter = recyclerAdapter
            layoutManager = LinearLayoutManager(context)
        }
        return view
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
