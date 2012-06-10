﻿<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"  xmlns:cml="http://www.xml-cml.org/schema"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:me="http://www.chem.leeds.ac.uk/mesmer"
  xmlns:svg="http://www.w3.org/2000/svg"
  xmlns:exsl="http://exslt.org/common"
  xmlns:math="http://exslt.org/math"
  xmlns:set="http://exslt.org/sets"
  extension-element-prefixes="exsl math set"
>

  <xsl:variable name="colors">
    <c>red</c>
    <c>green</c>
    <c>blue</c>
    <c>orange</c>
    <c>black</c>
    <c>teal</c>
  </xsl:variable>
  
  <xsl:variable name="popspecies" select="//me:analysis[1]/me:populationList[1]/me:population[1]/me:pop/@ref"/>
  
  <!--Make lists of the species and times being used for grain populations-->
  <xsl:variable name="grainspecies" select="set:distinct(//me:grainPopulation/@ref)"/>

  <!--============================================-->
  <xsl:template match="//me:analysis" mode="diagram">
    <xsl:if test="me:populationList">
      <p class="paramheader">
        <xsl:for-each select="me:parameters/@*">
          <xsl:value-of select="concat(name(),'=',.,'  ')"/>
        </xsl:for-each>
      </p>
    </xsl:if>
    <xsl:if test="count($popspecies)">
      <p class="poplabel">Species Populations</p>
    </xsl:if>
    
    <xsl:apply-templates select="me:populationList" mode="diagram"/>

    <xsl:if test="count($grainspecies)">
      <p class="poplabel">Grain Populations</p>
    </xsl:if>

    <xsl:apply-templates select="me:grainPopulationList"/>
    
  </xsl:template>

  <!--=========================================================================-->
  <xsl:template name="populationDiagram" match="me:populationList" mode="diagram">
    <xsl:variable name="p" select="me:population"/>

    <xsl:if test="position()=1">
      <xsl:call-template name="legend">
        <xsl:with-param name="nodes" select="$popspecies"/>
        <xsl:with-param name="ytext" select="'fractional population'"/>
        <xsl:with-param name="maxy" select="'1.0'"/>
        <xsl:with-param name="miny" select="'0.0'"/>
      </xsl:call-template>
      </xsl:if>

    <!--Frame of graph-->
    <svg:svg version="1.1" width="200px" height="220px">
      <svg:text x="30" y="14" font-family="Verdana" font-size="13">
        <xsl:value-of select="concat(@T,'K ',@conc)"/>
      </svg:text>
      <svg:rect x="1" y="21" width="198" height="158" fill="white" stroke="black" stroke-width="1"/>
      <xsl:variable name="startval" select="me:population[1]/@logTime"/>
      <xsl:variable name="endval" select="me:population[last()]/@logTime"/>
      <xsl:variable name="every" select="2"/>
      <!--value increment between ticks-->
      <xsl:call-template name="xaxis">
        <xsl:with-param name="val" select="$startval + 1.0"/>
        <!--label from -->
        <xsl:with-param name="maxval" select="$endval"/>
        <xsl:with-param name="pxperstep" select="(200 * $every) div ($endval - $startval)"/>
        <xsl:with-param name="xpx" select="200 div ($endval - $startval)"/>
        <xsl:with-param name="ypx" select="180"/>
        <xsl:with-param name="every" select="$every"/>
      </xsl:call-template>
      <svg:text text-anchor="middle"  font-family="Verdana" font-size="10">
        <xsl:attribute name="x">
          <xsl:value-of select="100"/>
        </xsl:attribute>
        <xsl:attribute name="y">
          <xsl:value-of select="208"/>
        </xsl:attribute>
        log10(time/secs)
      </svg:text>

      <!--Contents of graph-->
      <svg:svg y="20" height="160" preserveAspectRatio="none">
        <xsl:attribute name="viewBox">
          <xsl:value-of select="concat($startval, ' -1.0 ', $endval - $startval, ' 1.0')"/>
        </xsl:attribute>
        <xsl:for-each select="me:population[1]/me:pop/@ref">
          <!--for each species-->
          <svg:path fill="none" stroke-width="0.02" >
            <xsl:attribute name="stroke">
              <xsl:variable name="pos" select="position()"/>
              <xsl:value-of select="exsl:node-set($colors)/c[$pos]"/>
            </xsl:attribute>
            <xsl:attribute name="d">
              <xsl:variable name="cursp" select="."/>
              <xsl:value-of select="concat('M ', $p/@logTime ,' -1.0 L ')"/>
              <xsl:for-each select="$p/me:pop[@ref=$cursp]">
                <xsl:value-of select="concat(../@logTime,' -', ., ' ')"/>
                <!--see note at end-->
              </xsl:for-each>
            </xsl:attribute>
          </svg:path>
        </xsl:for-each>
      </svg:svg>
    </svg:svg>
  </xsl:template>

  <!--===================================================-->
  <!--Draw legend and y axis labelling-->
  <xsl:template name="legend">
    <xsl:param name="nodes"/>
    <xsl:param name="ytext"/>
    <xsl:param name="maxy"/>
    <xsl:param name="miny"/>
    <xsl:param name="headertext"/>
    <svg:svg width="160" height="200">

      <!--legend-->
      <xsl:if test="$headertext">
        <svg:text x="10" y="10" font-family="Verdana" font-size="12">
          <xsl:value-of select="$headertext"/>
        </svg:text>
      </xsl:if>
      <xsl:for-each select="$nodes">
        <xsl:variable name="pos" select="(position()-1)"/>
        <svg:line stroke-width="4" x1="10" x2="40">
          <xsl:attribute name="y1">
            <xsl:value-of select="24 + $pos*18"/>
          </xsl:attribute>
          <xsl:attribute name="y2">
            <xsl:value-of select="24 + $pos*18"/>
          </xsl:attribute>
          <xsl:attribute name="stroke">
            <xsl:value-of select="exsl:node-set($colors)/c[$pos+1]"/>
          </xsl:attribute>
        </svg:line>
        <svg:text x="50" font-family="Verdana" font-size="12">
          <xsl:attribute name="y">
            <xsl:value-of select="29 + $pos*18"/>
          </xsl:attribute>
          <xsl:value-of select="."/>
        </svg:text>
      </xsl:for-each>
      
      <!--y axis labelling-->
      <svg:g font-family="Verdana" font-size="10">
        <svg:text x="128" y="8">
          <xsl:value-of select="$maxy"/>
        </svg:text>
        <svg:text x="128" y="160">
          <xsl:value-of select="$miny"/>
        </svg:text>
        <svg:text x="-138" y="144" transform="rotate(-90)">
          <xsl:value-of select="$ytext"/>
        </svg:text>
      </svg:g>
    </svg:svg>
  </xsl:template>

  <!--=================================================================-->
  <!--Called recursively to add the tick marks and labels on the x-axis-->
  <xsl:template name="xaxis">
    <xsl:param name="val"/>
    <xsl:param name="maxval"/>
    <xsl:param name="xpx"/>
    <xsl:param name="ypx"/>
    <xsl:param name="pxperstep"/>
    <xsl:param name="every"/>
    <xsl:if test="$val &lt; $maxval">
      <!--tick-->
      <svg:path stroke="black">
        <xsl:attribute name="d">
          <xsl:value-of select="concat(' M ', $xpx, ' ', $ypx)"/>
          <xsl:value-of select="concat(' l 0 ', 5)"/>
        </xsl:attribute>
      </svg:path>
      <!--tick label-->
      <svg:text text-anchor="middle"  font-family="Verdana" font-size="10">
        <xsl:attribute name="x">
          <xsl:value-of select="$xpx"/>
        </xsl:attribute>
        <xsl:attribute name="y">
          <xsl:value-of select="$ypx + 15"/>
        </xsl:attribute>
        <xsl:value-of select="$val"/>
      </svg:text>
      <xsl:call-template name="xaxis">
        <xsl:with-param name="val" select="$val + $every"/>
        <xsl:with-param name="maxval" select="$maxval"/>
        <xsl:with-param name="pxperstep" select="$pxperstep"/>
        <xsl:with-param name="xpx" select="$xpx + $pxperstep"/>
        <xsl:with-param name="ypx" select="$ypx"/>
        <xsl:with-param name="every" select="$every"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

  <!--===================================================-->
  <!--Draw the lines for each time-->
  <xsl:template name="grainPopLines">
    <xsl:param name="nodes"/>
    <xsl:for-each select="$nodes/@time">
      <xsl:variable name="pos" select="position()"/>
      <svg:path fill="none" stroke-width =".002">
        <xsl:attribute name="stroke">
          <xsl:value-of select="exsl:node-set($colors)/c[$pos]"/>
        </xsl:attribute>
        <xsl:attribute name="d">
          <xsl:variable name="curtime" select="."/>
          <xsl:value-of select="concat('M 0 0',' L ')"/>
          <xsl:for-each select="$nodes[@time=$curtime]/me:grain">
            <xsl:value-of select="concat(' ',./@energy, ' -', .)"/>
          </xsl:for-each>
        </xsl:attribute>
      </svg:path>
    </xsl:for-each>
  </xsl:template>

  <!--===================================================-->
  <xsl:template match="me:grainPopulation">
    <xsl:variable name="pos" select="position()"/>
    <xsl:variable name="graintimes" select="set:distinct(../me:grainPopulation[@ref=current()/@ref]/@time)"/>
    <xsl:variable name="ymax" select="math:max(//me:grainPopulation/me:grain)"/>
    <xsl:if test="position()=2"> <!--why 2 and not 1?-->
      <div/> <!--to put each set of conditions on a separate line-->
      <xsl:call-template name="legend">
        <xsl:with-param name="nodes" select="$graintimes"/>
        <xsl:with-param name="ytext" select="'normalised grain pop'"/>
        <xsl:with-param name="maxy" select="$ymax"/>
        <xsl:with-param name="miny" select="'0.0'"/>
        <xsl:with-param name="headertext" select="'Time, seconds'"/>
      </xsl:call-template>
    </xsl:if>
    
    <xsl:variable name="startval" select="0"/>
    <xsl:variable name="endval" select="math:max(//me:grainPopulation/me:grain/@energy)"/>
    <xsl:if test="@time=$graintimes[1]">
      <!--Frame of graph, drawn only once for each set of times-->
      <svg:svg version="1.1" width="200px" height="220px">
        <!--species title on top of graph-->
        <svg:text x="1" y="14" font-family="Verdana" font-size="13" stroke="teal">
          <xsl:value-of select="@ref"/>
        </svg:text>
        <svg:text x="190" y="14"  text-anchor="end" font-family="Verdana" font-size="13">
          <xsl:value-of select="concat(../@T, 'K ', ../@conc)"/>
        </svg:text>
        <svg:rect x="1" y="21" width="198" height="158" fill="white" stroke="black" stroke-width="1"/>
        <xsl:variable name="every" select="4000"/>
        <xsl:call-template name="xaxis">
          <xsl:with-param name="val" select="$startval"/>
          <xsl:with-param name="maxval" select="$endval"/>
          <xsl:with-param name="pxperstep" select="(200 * $every) div ($endval - $startval)"/>
          <xsl:with-param name="xpx" select="200 div ($endval - $startval)"/>
          <xsl:with-param name="ypx" select="180"/>
          <xsl:with-param name="every" select="$every"/>
        </xsl:call-template>
        <svg:text text-anchor="middle"  font-family="Verdana" font-size="10">
          <xsl:attribute name="x">
            <xsl:value-of select="100"/>
          </xsl:attribute>
          <xsl:attribute name="y">
            <xsl:value-of select="208"/>
          </xsl:attribute>
          <xsl:value-of select="concat('grain energy, ', @units)"/>
        </svg:text>
        
        <!--Contents of graph-->
        <!--Viewbox puts -ymax at top and 0 at bottom. Values are negated before plotting.-->
        <svg:svg y="20" height="160" preserveAspectRatio="none" stroke="teal">
          <xsl:attribute name="viewBox">
            <xsl:value-of select="concat($startval, ' ', -$ymax, ' ', $endval - $startval, ' ',$ymax)"/>
          </xsl:attribute>
          <!--Draw lines a single species and all times-->
          <xsl:call-template name="grainPopLines">
            <xsl:with-param name="nodes" select="../me:grainPopulation[@ref=current()/@ref]"/>
          </xsl:call-template>
        </svg:svg>
      </svg:svg>
    </xsl:if>
  </xsl:template>
  
  <!-- Probably because XPath 1.0 doesn't use scientific numbers, some numbers give NaN when  
       arithmetic is done on them in XSLT before passing on to SVG. Consequently, the minus
       sign needed to invert the y axis is provided separately and the number is presumably
       handled as a string.-->
</xsl:stylesheet>
