
# FeatureExtraction_DataClean_BreakDataIntoLaps

<!--
The following template is based on:
Best-README-Template
Search for this, and you will find!
>
<!-- PROJECT LOGO -->
<br />
<p align="center">
  <!-- <a href="https://github.com/ivsg-psu/FeatureExtraction_Association_PointToPointAssociation">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->

  <h2 align="center"> FeatureExtraction_DataClean_BreakDataIntoLaps
  </h2>

  <pre align="center">
    <img src=".\Images\RaceTrack.jpg" alt="main laps picture" width="960" height="540">
    <!--figcaption>Fig.1 - The typical progression of map generation.</figcaption -->
    <!--font size="-2">Photo by <a href="https://unsplash.com/ko/@samuelchenard?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Samuel Chenard</a> on <a href="https://unsplash.com/photos/Bdc8uzY9EPw?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">Unsplash</a></font -->
</pre>

  <p align="center">
    The purpose of this code is to break data into "laps", e.g. segments of data that are defined by a clear start condition and end condition. The code finds when a given path meets the "start" condition, then meets the "end" condition, and returns every portion of the path that is inside both conditions. Advanced features of the code include the ability to return the row indices defining each lap's data, as well as the path portions prior and after the lap area in case the "run in" or "run out" areas are needed. Yay! (I think)
    <br />
    <!-- a href="https://github.com/ivsg-psu/FeatureExtraction_Association_PointToPointAssociation"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/ivsg-psu/FeatureExtraction_Association_PointToPointAssociation/tree/main/Documents">View Demo</a>
    <a href="https://github.com/ivsg-psu/FeatureExtraction_Association_PointToPointAssociation/issues">Report Bug</a>
    <a href="https://github.com/ivsg-psu/FeatureExtraction_Association_PointToPointAssociation/issues">Request Feature</a -->
  </p>
</p>

***

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About the Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="structure">Repo Structure</a>
      <ul>
        <li><a href="#directories">Top-Level Directories</li>
        <li><a href="#dependencies">Dependencies</li>
      </ul>
    </li>
    <li><a href="#functions">Functions</li>
      <ul>
        <li><a href="#basic-support-functions">Basic Support Functions</li>
        <ul>
          <li><a href="#fcn_laps_plotlapsxy">fcn_Laps_plotLapsXY - Plotting utility for lap outputs</li>
          <li><a href="#fcn_laps_fillsamplelaps">fcn_Laps_fillSampleLaps - Creates test datasets</li>
          <li><a href="#fcn_laps_plotzonedefinition">fcn_Laps_plotZoneDefinition - Plots zone definitions</li>
          <li><a href="#fcn_laps_fillsamplelaps">fcn_Laps_fillSampleLaps - Creates test datasets</li>
        </ul>
        <li><a href="#core-functions">Core Functions</li>
        <ul>
          <li><a href="#fcn_laps_breakdataintolaps">fcn_Laps_breakDataIntoLaps - Core function of the repo, breaks data into laps</li>
          <li><a href="#fcn_laps_checkzonetype">fcn_Laps_checkZoneType - Checks inputs to determine if zone is a point or line segment type</li>
          <li><a href="#fcn_laps_breakdataintolapindices">fcn_Laps_breakDataIntoLapIndices - A more advanced version of fcn_Laps_breakDataIntoLaps, where the outputs are the indices that apply to each lap.</li>
          <li><a href="#fcn_laps_findsegmentzonestartstop">fcn_Laps_findSegmentZoneStartStop - Supporting function that finds the portions of a path that meet a segment zone criteria</li>
          <li><a href="#fcn_laps_findpointzonestartstopandminimum">fcn_Laps_findPointZoneStartStopAndMinimum - Supporting function that finds the portions of a path that meet a point zone criteria</li>
        </ul>
      </ul>
    <li><a href="#usage">Usage</a></li>
     <ul>
     <li><a href="#general-usage">General Usage</li>
     <li><a href="#examples">Examples</li>
     <li><a href="#definition-of-endpoints">Definition of Endpoints</li>
     </ul>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

***

<!-- ABOUT THE PROJECT -->
## About The Project

<!--[![Product Name Screen Shot][product-screenshot]](https://example.com)-->

The most common location of our testing is the Larson Test Track, and we regularly use “laps around the track” as replicates, hence the name of the library. And when not on the test track and on public roads, data often needs to be segmented from one keypoint to another. For example, it is a common task to seek a subset of path data that resides only from one intersection to the next. While one could segment this data during data collection by simply stopping the vehicle recordings at each segment, it is impractical and dangerous to stop data collection at each and every possible intersection or feature point. Rather, vehicle or robot data is often collected by repeated driving of an area over/over without stopping. So, the final data set may contain many replicates of the area of interest.

This "Laps" code assists in breaking recorded path data into paths by defining specific start and end locations, for example from intersection "A" to stop sign "B". Specifically, the purpose of this code is to break data into "laps", e.g. segments of data that are defined by a clear start condition and end condition. The code finds when a given path meets the "start" condition, then meets the "end" condition, and returns every portion of the path that is inside both conditions. There are many advanced features as well including the ability to define excursion points, the number of points that must be within a condition for it to activate, and the ability to extract the portions of the paths before and after each lap, in addition to the data for each lap.

* Inputs:
  * either a "traversals" type, as explained in the Path library, or a path of XY points in N x 2 format
  * the start, end, and optional excursions can be entered as either a line segment or a point and radius.  
* Outputs
  * Separate arrays of XY points, or of indices for the lap, with one array for each lap
  * The function also can return the points that were not used for laps, e.g. the points before the first start and after the last end

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

<!-- GETTING STARTED -->
## Getting Started


### Pole Status

<pre align="center">
  <img src=".\Images\Pole_Status.jpg" alt="Pole Status" width="720" height="440">
<figcaption> Pole Status </figcaption>
</pre>

The RSU ID is corresponding to the numbered RSUs in the <a href="### Serial Numbers of RSUs:"> Serial Numbers of RSUs</a> section.

<a href="#hardware_cv2x_commsignia">Back to top</a>

***

### Purchasing

<pre align="center">
1.
  <img src=".\Images\Lightning_Protection_Package_1.JPG" alt="Lightning_Protection_Package_1" width="720" height="960">
<figcaption>Lightning Protection Package and Cabinet Status Monitoring 1</figcaption>

2.
  <img src=".\Images\Lightning_Protection_Package_2.JPG" alt="Lightning_Protection_Package_2" width="720" height="960">
<figcaption>Lightning Protection Package and Cabinet Status Monitoring 2</figcaption>
</pre>

The following items are in the lightning protection and cabinet status monitoring packages:

| Item | Quantity |
|-----------------------------------------------|---|
| 1"*25' PVC Conduit | 6 |
| Copper Lightning Rod Kit (Without Ground Rod) | 4 |
| Arduino Uno | 6 |
| 1" Conduit Strap| 50 |
| Magnetic Reed Switch MC-32 | 12 |
| Robot 5MM LDR Photosensitive Sensor | 20 |
| DHT22 Temperature and Humidity Sensor | 12 |
| Water sensor detector | 10 |
| LED night lights (Dusk to Dawn Sensor) | 12 |

<a href="#hardware_cv2x_commsignia">Back to top</a>

***


<!-- USAGE EXAMPLES -->
## Usage
<!-- Use this space to show useful examples of how a project can be used.
Additional screenshots, code examples and demos work well in this space. You may
also link to more resources. -->

### General Usage

Each of the functions has an associated test script, using the convention

```sh
script_test_fcn_fcnname
```

where fcnname is the function name as listed above.

As well, each of the functions includes a well-documented header that explains inputs and outputs. These are supported by MATLAB's help style so that one can type:

```sh
help fcn_fcnname
```

for any function to view function details.

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

### Examples

1. Run the main script to set up the workspace and demonstrate main outputs, including the figures included here:

   ```sh
   script_demo_Laps
   ```

    This exercises the main function of this code.

2. After running the main script to define the included directories for utility functions, one can then navigate to the Functions directory and run any of the functions or scripts there as well. All functions for this library are found in the Functions sub-folder, and each has an associated test script. Run any of the various test scripts; each can work as a stand-alone script.

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

### Definition of Endpoints

The codeset uses two types of zone definitions:

1. A point location defined by the center and radius of the zone, and number of points that must be within this zone. An example of this would be "travel from home" or "to grandma's house". The point "zone" specification is given by an X,Y center location and a radius in the form of [X Y radius], as a 3x1 matrix. Whenever the path passes within the radius with a specified number of points within that radius, the minimum distance point then "triggers" the zone.

    <img src=".\Images\point_zone_definition.png" alt="point_zone_definition picture" width="200" height="200">

2. A line segment. An example is the start line or finish line of a race. A runner has not started or ended the race without crossing these lines. For line segment conditions, the inputs are condition formatted as: [X_start Y_start; X_end Y_end] wherein start denotes the starting coordinate of the line segment, end denotes the ending coordinate of the line segment. The direction of start/end lines of the segment are defined such that a correct crossing of the line is in the positive cross-product direction defined from the vector from start to end of the segment.

    <img src=".\Images\linesegment_zone_definition.png" alt="linesegment_zone_definition picture" width="200" height="200">

These two conditions can be mixed and matched, so that one could, for example, find every lap of data where someone went from a race start line (defined by a line segment) to a specific mountain peak defined by a point and radius.

The two zone types above can be used to define three types of conditions:

1. A start condition - where a lap starts. The lap does not end until and end condition is met.
2. An end condition - where a lap ends. The lap cannot end until this condition is met.
3. An excursion condition (optional) - a condition that must be met after the start point, and before the end point. The excursion condition must be met before the end point is counted.

Why is an excursion point needed? Consider an example: it is common for the start line of a marathon to be quite close to the start line, sometimes even just a few hundred feet after the start line. This setup is for the practical reason that runners do not want to make long walks to/from starting locations to finish location either before, and definitely not after, such a race. As a consequence, it is common that, immediately after the start of the race, a runner will cross the finish line before actually finishing the race. This happens in field data collection when one accidentally passes a start/end station, and then backs up the vehicle to reset. In using these data recordings, we would not want these small segment to count as a complete laps, for example the 100-ish meter distance to be counted as a marathon run. Rather, one would require that the recorded data enter some excursion zone far away from the starting line for such a "lap" to count. Thus, this laps code allows one to define an excursion point as a location far out into the course that one must "hit" before the finish line is counted as the actual "finish" of the lap.

* For each lap when there are repeats, the resulting laps of data include the lead-in and fade-out data, namely the datapoint immediately before the start condition was met, and the datapoint after the end condition is met. THIS CREATES REPLICATE DATA. However, this allows better merging of data for repeated laps, for example averaging data exactly from start to finish, or to more exactly calculate velocities on entry and exit of a lap by using windowed averages or filters.

* Points inside the lap can be set for the point-type zones. These occur as optional input arguments in fcn_Laps_findPointZoneStartStopAndMinimum and in the core definition of a point zone as the 2nd argument. For example, the following code:

  ```Matlab
  start_definition = [10 3 0 0]; % Radius 10, 3 points must pass near [0 0]
  ```

  requires 3 points to occur within the start zone area.

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

## Major release versions

This code is still in development (alpha testing)

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

<!-- CONTACT -->
## Contact

Sean Brennan - [sbrennan@psu.edu](sbrennan@psu.edu)

Project Link: [https://github.com/ivsg-psu/Hardware_CV2X_TrackBoxes](https://github.com/ivsg-psu/Hardware_CV2X_TrackBoxes)

<a href="#featureextraction_dataclean_breakdataintolaps">Back to top</a>

***

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
