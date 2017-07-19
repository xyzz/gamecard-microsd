<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.2.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="7" fill="1" visible="yes" active="yes"/>
<layer number="251" name="SMDround" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="untitled">
<packages>
<package name="CONNECTOR">
<wire x1="-7.5" y1="-2.5" x2="7.5" y2="-2.5" width="0.127" layer="51"/>
<wire x1="7.5" y1="-2.5" x2="7.5" y2="2.5" width="0.127" layer="51"/>
<wire x1="7.5" y1="2.5" x2="-7.5" y2="2.5" width="0.127" layer="51"/>
<wire x1="-7.5" y1="2.5" x2="-7.5" y2="-2.5" width="0.127" layer="51"/>
<smd name="GND" x="-6.3315" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="CMD" x="-4.9245" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="INS" x="-3.5175" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="DAT0" x="-2.1105" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="DAT1" x="-0.7035" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="DAT2" x="0.7035" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="DAT3" x="2.1105" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="CLK" x="3.5175" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="GND2" x="4.9245" y="0" dx="1.137" dy="5" layer="1"/>
<smd name="VCC" x="6.3315" y="0" dx="1.137" dy="5" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="CONNECTOR">
<wire x1="-12.7" y1="5.08" x2="-12.7" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-5.08" x2="15.24" y2="-5.08" width="0.254" layer="94"/>
<wire x1="15.24" y1="-5.08" x2="15.24" y2="5.08" width="0.254" layer="94"/>
<wire x1="15.24" y1="5.08" x2="-12.7" y2="5.08" width="0.254" layer="94"/>
<pin name="GND" x="-10.16" y="10.16" length="middle" direction="pwr" rot="R270"/>
<pin name="CMD" x="-7.62" y="10.16" length="middle" rot="R270"/>
<pin name="INS" x="-5.08" y="10.16" length="middle" rot="R270"/>
<pin name="DAT0" x="-2.54" y="10.16" length="middle" rot="R270"/>
<pin name="DAT1" x="0" y="10.16" length="middle" rot="R270"/>
<pin name="DAT2" x="2.54" y="10.16" length="middle" rot="R270"/>
<pin name="DAT3" x="5.08" y="10.16" length="middle" rot="R270"/>
<pin name="CLK" x="7.62" y="10.16" length="middle" rot="R270"/>
<pin name="GND@9" x="10.16" y="10.16" length="middle" direction="pwr" rot="R270"/>
<pin name="VCC" x="12.7" y="10.16" length="middle" direction="pwr" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CONNECTOR">
<gates>
<gate name="G$1" symbol="CONNECTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CONNECTOR">
<connects>
<connect gate="G$1" pin="CLK" pad="CLK"/>
<connect gate="G$1" pin="CMD" pad="CMD"/>
<connect gate="G$1" pin="DAT0" pad="DAT0"/>
<connect gate="G$1" pin="DAT1" pad="DAT1"/>
<connect gate="G$1" pin="DAT2" pad="DAT2"/>
<connect gate="G$1" pin="DAT3" pad="DAT3"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND@9" pad="GND2"/>
<connect gate="G$1" pin="INS" pad="INS"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="sd-mmc">
<packages>
<package name="TF-PULL-REVERSE">
<description>TF / Micro SD socket is PUSH-PUSH type, the card can be pushed into and auto locked and pushed out by simply press the card.
&lt;p&gt;
Surface Mounting type.</description>
<smd name="S1" x="7.9" y="2.85" dx="1.4" dy="2" layer="1" rot="R180"/>
<smd name="S2" x="-7.9" y="2.85" dx="1.4" dy="2" layer="1" rot="R180"/>
<smd name="S3" x="-7.96" y="-6.75" dx="1.28" dy="1.4" layer="1" rot="R180"/>
<smd name="1" x="2.2" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="2" x="1.1" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="3" x="0" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="4" x="-1.1" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="5" x="-2.2" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="6" x="-3.3" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="7" x="-4.4" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
<smd name="8" x="-5.5" y="-7.9" dx="0.7" dy="1.4" layer="1" rot="R180"/>
</package>
</packages>
<symbols>
<symbol name="TF9">
<wire x1="-7.62" y1="12.7" x2="-7.62" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-12.7" x2="10.16" y2="-12.7" width="0.254" layer="94"/>
<wire x1="10.16" y1="-12.7" x2="10.16" y2="12.7" width="0.254" layer="94"/>
<wire x1="10.16" y1="12.7" x2="-7.62" y2="12.7" width="0.254" layer="94"/>
<text x="-5.08" y="13.208" size="1.6764" layer="95">&gt;NAME</text>
<text x="10.668" y="10.16" size="1.6764" layer="96" rot="R270">&gt;VALUE</text>
<text x="9.398" y="-12.192" size="1.016" layer="97" rot="R90">TransFlash holder</text>
<pin name="DAT2" x="-12.7" y="10.16" length="middle"/>
<pin name="CD/DAT3(!CS!)" x="-12.7" y="7.62" length="middle"/>
<pin name="CMD(DI)" x="-12.7" y="5.08" length="middle"/>
<pin name="VDD" x="-12.7" y="2.54" length="middle" direction="pwr"/>
<pin name="CLK(SCLK)" x="-12.7" y="0" length="middle" direction="in"/>
<pin name="VSS" x="-12.7" y="-2.54" length="middle" direction="pwr"/>
<pin name="DAT0(DO)" x="-12.7" y="-5.08" length="middle"/>
<pin name="DAT1" x="-12.7" y="-7.62" length="middle"/>
<pin name="S1" x="-2.54" y="-15.24" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="S2" x="0" y="-15.24" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="S3" x="2.54" y="-15.24" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TF-HOLDER" prefix="SD">
<description>TF / Micro SD socket is PUSH-PUSH type, the card can be pushed into and auto locked and pushed out by simply press the card.
&lt;p&gt;
Surface Mounting type.</description>
<gates>
<gate name="G$1" symbol="TF9" x="0" y="0"/>
</gates>
<devices>
<device name="REVERSE" package="TF-PULL-REVERSE">
<connects>
<connect gate="G$1" pin="CD/DAT3(!CS!)" pad="2"/>
<connect gate="G$1" pin="CLK(SCLK)" pad="5"/>
<connect gate="G$1" pin="CMD(DI)" pad="3"/>
<connect gate="G$1" pin="DAT0(DO)" pad="7"/>
<connect gate="G$1" pin="DAT1" pad="8"/>
<connect gate="G$1" pin="DAT2" pad="1"/>
<connect gate="G$1" pin="S1" pad="S1"/>
<connect gate="G$1" pin="S2" pad="S2"/>
<connect gate="G$1" pin="S3" pad="S3"/>
<connect gate="G$1" pin="VDD" pad="4"/>
<connect gate="G$1" pin="VSS" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="untitled" deviceset="CONNECTOR" device=""/>
<part name="SD1" library="sd-mmc" deviceset="TF-HOLDER" device="REVERSE"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="-78.74" y="40.64" rot="R270"/>
<instance part="SD1" gate="G$1" x="12.7" y="38.1"/>
</instances>
<busses>
</busses>
<nets>
<net name="VCC" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="VCC"/>
<wire x1="-68.58" y1="27.94" x2="-15.24" y2="27.94" width="0.1524" layer="91"/>
<wire x1="-15.24" y1="27.94" x2="-15.24" y2="40.64" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="VDD"/>
<wire x1="-15.24" y1="40.64" x2="0" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GND@9"/>
<wire x1="-68.58" y1="30.48" x2="-63.5" y2="30.48" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="30.48" x2="-60.96" y2="30.48" width="0.1524" layer="91"/>
<wire x1="-60.96" y1="30.48" x2="-60.96" y2="45.72" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="-60.96" y1="45.72" x2="-60.96" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-60.96" y1="50.8" x2="-68.58" y2="50.8" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="30.48" x2="-63.5" y2="22.86" width="0.1524" layer="91"/>
<junction x="-63.5" y="30.48"/>
<wire x1="-63.5" y1="22.86" x2="-15.24" y2="22.86" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="INS"/>
<wire x1="-15.24" y1="22.86" x2="-10.16" y2="22.86" width="0.1524" layer="91"/>
<wire x1="-68.58" y1="45.72" x2="-60.96" y2="45.72" width="0.1524" layer="91"/>
<junction x="-60.96" y="45.72"/>
<wire x1="-10.16" y1="22.86" x2="-10.16" y2="35.56" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="VSS"/>
<wire x1="-10.16" y1="35.56" x2="0" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-15.24" y1="22.86" x2="-15.24" y2="15.24" width="0.1524" layer="91"/>
<junction x="-15.24" y="22.86"/>
<wire x1="-15.24" y1="15.24" x2="10.16" y2="15.24" width="0.1524" layer="91"/>
<wire x1="10.16" y1="15.24" x2="12.7" y2="15.24" width="0.1524" layer="91"/>
<wire x1="12.7" y1="15.24" x2="15.24" y2="15.24" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="S3"/>
<wire x1="15.24" y1="22.86" x2="15.24" y2="15.24" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="S2"/>
<wire x1="12.7" y1="22.86" x2="12.7" y2="15.24" width="0.1524" layer="91"/>
<junction x="12.7" y="15.24"/>
<pinref part="SD1" gate="G$1" pin="S1"/>
<wire x1="10.16" y1="22.86" x2="10.16" y2="15.24" width="0.1524" layer="91"/>
<junction x="10.16" y="15.24"/>
</segment>
</net>
<net name="CMD" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="CMD"/>
<wire x1="-68.58" y1="48.26" x2="-25.4" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="48.26" x2="-25.4" y2="43.18" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="CMD(DI)"/>
<wire x1="-25.4" y1="43.18" x2="0" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DAT0" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="DAT0"/>
<wire x1="-68.58" y1="43.18" x2="-27.94" y2="43.18" width="0.1524" layer="91"/>
<wire x1="-27.94" y1="43.18" x2="-27.94" y2="33.02" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="DAT0(DO)"/>
<wire x1="-27.94" y1="33.02" x2="0" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DAT1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="DAT1"/>
<wire x1="-68.58" y1="40.64" x2="-30.48" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="40.64" x2="-30.48" y2="30.48" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="DAT1"/>
<wire x1="-30.48" y1="30.48" x2="0" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DAT2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="DAT2"/>
<wire x1="-68.58" y1="38.1" x2="-20.32" y2="38.1" width="0.1524" layer="91"/>
<wire x1="-20.32" y1="38.1" x2="-20.32" y2="48.26" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="DAT2"/>
<wire x1="-20.32" y1="48.26" x2="0" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DAT3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="DAT3"/>
<wire x1="-68.58" y1="35.56" x2="-33.02" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="35.56" x2="-33.02" y2="45.72" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="45.72" x2="0" y2="45.72" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="CD/DAT3(!CS!)"/>
</segment>
</net>
<net name="CLK" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="CLK"/>
<wire x1="-68.58" y1="33.02" x2="-33.02" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="33.02" x2="-33.02" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="25.4" x2="-7.62" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="25.4" x2="-7.62" y2="38.1" width="0.1524" layer="91"/>
<pinref part="SD1" gate="G$1" pin="CLK(SCLK)"/>
<wire x1="-7.62" y1="38.1" x2="0" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
