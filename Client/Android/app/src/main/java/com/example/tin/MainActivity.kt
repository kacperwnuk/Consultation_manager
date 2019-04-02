package com.example.tin

import android.os.Bundle
import android.support.design.widget.NavigationView
import android.support.v4.view.GravityCompat
import android.support.v7.app.ActionBarDrawerToggle
import android.support.v7.app.AppCompatActivity
import android.view.Menu
import android.view.MenuItem
import com.example.tin.data.CredentialsManager
import com.google.android.gms.auth.api.credentials.Credential
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.app_bar_main.*

class MainActivity : AppCompatActivity(), NavigationView.OnNavigationItemSelectedListener, ReserveConsultationFragment.ActionListener {

    private var credential: Credential? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setSupportActionBar(toolbar)
        setContentView(R.layout.activity_main)

        val reserveConsultationFragment = ReserveConsultationFragment.newInstance("", "")
        supportFragmentManager.beginTransaction().replace(R.id.fragment_container, reserveConsultationFragment).commit()

        val toggle = ActionBarDrawerToggle(
            this, drawer_layout, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close
        )
        drawer_layout.addDrawerListener(toggle)
        toggle.syncState()
        nav_view.setNavigationItemSelectedListener(this)
        if (savedInstanceState != null) {
            return
        }
        credential = intent.extras.get("Credential") as Credential?
    }

    override fun onBackPressed() {
        if (drawer_layout.isDrawerOpen(GravityCompat.START)) {
            drawer_layout.closeDrawer(GravityCompat.START)
        } else {
            super.onBackPressed()
        }
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        return when (item.itemId) {
            R.id.action_settings -> true
            else -> super.onOptionsItemSelected(item)
        }
    }

    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        // Handle navigation view item clicks here.
        when (item.itemId) {
            R.id.find_consultation -> {
                supportFragmentManager.beginTransaction().replace(R.id.fragment_container, ReserveConsultationFragment.newInstance("", ""))
                    .addToBackStack(null).commit()
            }
            R.id.my_consultations -> {
                supportFragmentManager.beginTransaction().replace(R.id.fragment_container, ViewReservedConsultationsFragment.newInstance("", ""))
                    .addToBackStack(null).commit()
            }
            R.id.suggest_consultation -> {
                supportFragmentManager.beginTransaction().replace(R.id.fragment_container, SuggestConsultationFragment.newInstance(null, null, null, ""))
                    .addToBackStack(null).commit()
            }
            R.id.nav_share -> {

            }
            R.id.log_out -> {
                CredentialsManager(this).deleteCredentials(credential)
                finish()
            }
        }

        drawer_layout.closeDrawer(GravityCompat.START)
        return true
    }

    override fun addBefore(day: String, endTime: String) {
        supportFragmentManager.beginTransaction().replace(R.id.fragment_container, SuggestConsultationFragment.newInstance(null, endTime, day, ""))
            .addToBackStack(null).commit()
    }

    override fun addAfter(day: String, startTime: String) {
        supportFragmentManager.beginTransaction().replace(R.id.fragment_container, SuggestConsultationFragment.newInstance(startTime, null, day,""))
            .addToBackStack(null).commit()
    }

    override fun reserve() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }
}
