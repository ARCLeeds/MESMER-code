/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Controls.java
 *
 * Created on 14-Dec-2010, 17:26:39
 */



/**
 *
 * @author mhh
 */
public class Controls extends javax.swing.JPanel {

    public String bufferGas = "He - Helium";
    public String calcMethod = "Fitting";


    /** Creates new form Controls */
    public Controls() {
        initComponents();
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jTextField1 = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        jComboBox1 = new javax.swing.JComboBox();
        jCheckBox2 = new javax.swing.JCheckBox();
        jCheckBox3 = new javax.swing.JCheckBox();
        jCheckBox4 = new javax.swing.JCheckBox();
        jCheckBox5 = new javax.swing.JCheckBox();
        jCheckBox6 = new javax.swing.JCheckBox();
        jCheckBox7 = new javax.swing.JCheckBox();
        jCheckBox8 = new javax.swing.JCheckBox();
        jCheckBox9 = new javax.swing.JCheckBox();
        jCheckBox10 = new javax.swing.JCheckBox();
        jCheckBox11 = new javax.swing.JCheckBox();
        jCheckBox12 = new javax.swing.JCheckBox();
        jCheckBox13 = new javax.swing.JCheckBox();
        jCheckBox14 = new javax.swing.JCheckBox();
        jCheckBox15 = new javax.swing.JCheckBox();
        jCheckBox16 = new javax.swing.JCheckBox();
        jCheckBox17 = new javax.swing.JCheckBox();
        jCheckBox19 = new javax.swing.JCheckBox();
        jLabel4 = new javax.swing.JLabel();
        jComboBox2 = new javax.swing.JComboBox();

        setMinimumSize(new java.awt.Dimension(807, 350));
        setPreferredSize(new java.awt.Dimension(807, 300));
        setLayout(null);

        jLabel1.setFont(new java.awt.Font("Tahoma", 1, 16));
        jLabel1.setText("Controls");
        add(jLabel1);
        jLabel1.setBounds(340, 10, 130, 14);

        jLabel2.setFont(new java.awt.Font("Tahoma", 0, 14));
        jLabel2.setText("Eigenvalues ");
        add(jLabel2);
        jLabel2.setBounds(20, 60, 90, 17);

        jTextField1.setFont(new java.awt.Font("Tahoma", 0, 14));
        jTextField1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField1ActionPerformed(evt);
            }
        });
        add(jTextField1);
        jTextField1.setBounds(100, 50, 140, 30);

        jLabel3.setFont(new java.awt.Font("Tahoma", 0, 14));
        jLabel3.setText("CalcMethod");
        add(jLabel3);
        jLabel3.setBounds(500, 60, 100, 17);

        jComboBox1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Fitting", "Simple", "Gridsearch" }));
        jComboBox1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBox1ActionPerformed(evt);
            }
        });
        add(jComboBox1);
        jComboBox1.setBounds(610, 60, 150, 20);

        jCheckBox2.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox2.setText("printCellDOS ");
        jCheckBox2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox2ActionPerformed(evt);
            }
        });
        add(jCheckBox2);
        jCheckBox2.setBounds(330, 100, 200, 25);

        jCheckBox3.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox3.setText("printReactionOperatorColumnSums");
        add(jCheckBox3);
        jCheckBox3.setBounds(20, 130, 280, 25);

        jCheckBox4.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox4.setText("printGrainkbE");
        add(jCheckBox4);
        jCheckBox4.setBounds(20, 160, 190, 25);

        jCheckBox5.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox5.setText("printReactionOperatorSize");
        add(jCheckBox5);
        jCheckBox5.setBounds(20, 190, 220, 25);

        jCheckBox6.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox6.setText("printTunnellingCoefficients");
        jCheckBox6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox6ActionPerformed(evt);
            }
        });
        add(jCheckBox6);
        jCheckBox6.setBounds(20, 220, 220, 25);

        jCheckBox7.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox7.setText("testRateConstants");
        jCheckBox7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox7ActionPerformed(evt);
            }
        });
        add(jCheckBox7);
        jCheckBox7.setBounds(20, 250, 200, 25);

        jCheckBox8.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox8.setText("printGrainBoltzmann");
        jCheckBox8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox8ActionPerformed(evt);
            }
        });
        add(jCheckBox8);
        jCheckBox8.setBounds(330, 130, 190, 25);

        jCheckBox9.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox9.setText("printGrainkfE");
        add(jCheckBox9);
        jCheckBox9.setBounds(330, 160, 180, 25);

        jCheckBox10.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox10.setText("printSpeciesProfile ");
        add(jCheckBox10);
        jCheckBox10.setBounds(330, 190, 160, 25);

        jCheckBox11.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox11.setText("testDOS");
        add(jCheckBox11);
        jCheckBox11.setBounds(330, 220, 110, 25);

        jCheckBox12.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox12.setText("useTheSameCellNumberForAllConditions");
        jCheckBox12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox12ActionPerformed(evt);
            }
        });
        add(jCheckBox12);
        jCheckBox12.setBounds(330, 250, 280, 25);

        jCheckBox13.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox13.setText("printCellTransitionStateFlux");
        add(jCheckBox13);
        jCheckBox13.setBounds(570, 100, 210, 25);

        jCheckBox14.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox14.setText("printGrainDOS");
        jCheckBox14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox14ActionPerformed(evt);
            }
        });
        add(jCheckBox14);
        jCheckBox14.setBounds(570, 130, 150, 25);

        jCheckBox15.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox15.setText("printGrainTransitionStateFlux");
        add(jCheckBox15);
        jCheckBox15.setBounds(570, 160, 240, 25);

        jCheckBox16.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox16.setText("printTunnelingCoefficients");
        jCheckBox16.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox16ActionPerformed(evt);
            }
        });
        add(jCheckBox16);
        jCheckBox16.setBounds(570, 190, 210, 25);

        jCheckBox17.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox17.setText("testMicroRates");
        add(jCheckBox17);
        jCheckBox17.setBounds(570, 220, 160, 25);

        jCheckBox19.setFont(new java.awt.Font("Tahoma", 0, 14));
        jCheckBox19.setText("calculateRateCoefficientsOnly");
        jCheckBox19.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox19ActionPerformed(evt);
            }
        });
        add(jCheckBox19);
        jCheckBox19.setBounds(20, 100, 280, 25);

        jLabel4.setFont(new java.awt.Font("Tahoma", 0, 14));
        jLabel4.setText("Buffer Gas");
        add(jLabel4);
        jLabel4.setBounds(260, 60, 90, 17);

        jComboBox2.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "He - Helium", "N2 - Nitrogen" }));
        jComboBox2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBox2ActionPerformed(evt);
            }
        });
        add(jComboBox2);
        jComboBox2.setBounds(360, 60, 110, 20);
    }// </editor-fold>//GEN-END:initComponents

    public String getEigenvalues()
    {
        return jTextField1.getText();
    }

    private void jTextField1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jTextField1ActionPerformed

    private void jCheckBox19ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox19ActionPerformed
        // TODO add your handling code here:
        boolean checkBox = jCheckBox19.isSelected();
        System.out.println(" Checked************* " +checkBox );
    }//GEN-LAST:event_jCheckBox19ActionPerformed

    private void jCheckBox6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox6ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox6ActionPerformed

    private void jCheckBox7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox7ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox7ActionPerformed

    private void jCheckBox2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox2ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox2ActionPerformed

    private void jCheckBox8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox8ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox8ActionPerformed

    private void jCheckBox12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox12ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox12ActionPerformed

    private void jCheckBox14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox14ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox14ActionPerformed

    private void jCheckBox16ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox16ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCheckBox16ActionPerformed

    private void jComboBox2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBox2ActionPerformed
        // TODO add your handling code here:
        bufferGas = (String) jComboBox2.getSelectedItem();

    }//GEN-LAST:event_jComboBox2ActionPerformed

    private void jComboBox1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBox1ActionPerformed
        // TODO add your handling code here:
        calcMethod = (String) jComboBox1.getSelectedItem();
    }//GEN-LAST:event_jComboBox1ActionPerformed


    public String get_BufferGas()
    {

        return bufferGas.equals("He - Helium")? "He" : "N2";
    }

    public String get_CalcMethod()
    {
        return calcMethod;
    }

    public boolean get_calculateRateCoefficientsOnly()
    {
        return  jCheckBox19.isSelected();
    }

    public boolean get_printReactionOperatorColumnSums()
    {
        return jCheckBox3.isSelected();
    }

    public boolean get_printGrainkbE()
    {
        return  jCheckBox4.isSelected();
    }

    public boolean get_printReactionOperatorSize()
    {
        return  jCheckBox5.isSelected();
    }

    public boolean get_printTunnellingCoefficients()
    {
        return  jCheckBox6.isSelected();
    }

    public boolean get_testRateConstants()
    {
        return  jCheckBox7.isSelected();
    }

    public boolean get_printCellDOS ()
    {
        return  jCheckBox2.isSelected();
    }

    public boolean get_printGrainBoltzmann()
    {
        return  jCheckBox8.isSelected();
    }

    public boolean get_printGrainkfE()
    {
        return  jCheckBox9.isSelected();
    }

    public boolean get_printSpeciesProfile ()
    {
        return  jCheckBox10.isSelected();
    }

    public boolean get_testDOS()
    {
        return  jCheckBox11.isSelected();
    }

    public boolean get_useTheSameCellNumberForAllConditions()
    {
        return  jCheckBox12.isSelected();
    }

    public boolean get_printCellTransitionStateFlux()
    {
        return  jCheckBox13.isSelected();
    }

    public boolean get_printGrainDOS()
    {
        return  jCheckBox14.isSelected();
    }

    public boolean get_printGrainTransitionStateFlux()
    {
        return  jCheckBox15.isSelected();
    }

    public boolean get_printTunnelingCoefficients()
    {
        return  jCheckBox16.isSelected();
    }

    public boolean get_testMicroRates()
    {
        return  jCheckBox17.isSelected();
    }

    public String get_Eigenvalues()
    {
        return jTextField1.getText();
    }


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JCheckBox jCheckBox10;
    private javax.swing.JCheckBox jCheckBox11;
    private javax.swing.JCheckBox jCheckBox12;
    private javax.swing.JCheckBox jCheckBox13;
    private javax.swing.JCheckBox jCheckBox14;
    private javax.swing.JCheckBox jCheckBox15;
    private javax.swing.JCheckBox jCheckBox16;
    private javax.swing.JCheckBox jCheckBox17;
    private javax.swing.JCheckBox jCheckBox19;
    private javax.swing.JCheckBox jCheckBox2;
    private javax.swing.JCheckBox jCheckBox3;
    private javax.swing.JCheckBox jCheckBox4;
    private javax.swing.JCheckBox jCheckBox5;
    private javax.swing.JCheckBox jCheckBox6;
    private javax.swing.JCheckBox jCheckBox7;
    private javax.swing.JCheckBox jCheckBox8;
    private javax.swing.JCheckBox jCheckBox9;
    private javax.swing.JComboBox jComboBox1;
    private javax.swing.JComboBox jComboBox2;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JTextField jTextField1;
    // End of variables declaration//GEN-END:variables

}
