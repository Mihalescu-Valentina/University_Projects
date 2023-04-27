using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;


namespace Lab1_DBMS
{
    public partial class Form1 : Form
    {

        SqlConnection conn;
        SqlDataAdapter daHostCity;
        SqlDataAdapter daVenue;
        DataSet dset;
        BindingSource bsVenue;
        BindingSource bsHostCity;
        SqlCommandBuilder cmdBuilder;
        string queryVenue;
        string queryHostCity;

        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        string getConnectionString()
        {
            return "Data Source=DESKTOP-0B90NMB;" + "Initial Catalog=Eurovision;Integrated Security=true;";
        }

        void FillData()
        {
            conn = new SqlConnection(getConnectionString());
            queryVenue = "SELECT * FROM Venue";
            queryHostCity = "SELECT * FROM HostCity";

            daVenue = new SqlDataAdapter(queryVenue, conn);
            daHostCity = new SqlDataAdapter(queryHostCity, conn);
            dset = new DataSet();
            daVenue.Fill(dset, "Venue");
            daHostCity.Fill(dset, "HostCity");

            cmdBuilder = new SqlCommandBuilder(daVenue);
            dset.Relations.Add("HostCityVenue", dset.Tables["HostCity"].Columns["host_city_id"], dset.Tables["Venue"].Columns["host_city_id"]);
            bsHostCity = new BindingSource();
            bsHostCity.DataSource = dset.Tables["HostCity"];
            bsVenue = new BindingSource(bsHostCity, "HostCityVenue");
            this.dataGridView1.DataSource = bsHostCity;
            this.dataGridView2.DataSource = bsVenue;

            cmdBuilder.GetUpdateCommand();


        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            daVenue.Update(dset, "Venue");
        }


    }
}
