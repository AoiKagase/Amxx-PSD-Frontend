{% extends 'inc_base.tpl' %}
{% block title   %}Top Ranking{% endblock %}
{% block content %}
		<table>
			<thead>
			<tr>
				<td colspan="23" class="catHead">
					<span class="genmed"><b>Player Ranking TOP 10</b></span>
				</td>
			</tr>
			</thead>
		</table>
		<table class="table table-hover">
			<thead>
			<tr>
				<td scope="col" rowspan="2">Rank</td>
				<td scope="col" rowspan="2"></td>
				<td scope="col" rowspan="2"></td>
				<td scope="col" rowspan="2">Name</td>
				<td scope="col" rowspan="2">Play Time</td>
				<td scope="col" rowspan="2">Score</td>
				<td scope="col" rowspan="2">Kills</td>
				<td scope="col" rowspan="2">Deaths</td>
				<td scope="col" rowspan="2">TeamKills</td>
				<td scope="col" rowspan="2">ELO</td>
				<!--
				<td scope="col" rowspan="2">Hits</td>
				<td scope="col" rowspan="2">Damages</td>
				<td scope="col" rowspan="2">Shots</td>
				<td scope="col" rowspan="2">HeadShots</td>
				<td scope="col" rowspan="2">Efficiency.</td>
				<td scope="col" rowspan="2">Accuracy.</td>
				<td scope="col" rowspan="2">Accuracy<br />HeadShots.</td>
				<td scope="col" rowspan="2">K/D Rate.</td>
				<td scope="col" colspan="7">HIT POSITION.</td>
				-->
			</tr>
			<!--
			<tr>
				<td scope="col">HEAD</td>
				<td scope="col">CHEST</td>
				<td scope="col">STOMACH</td>
				<td scope="col">LEFT ARM</td>
				<td scope="col">RIGHT ARM</td>
				<td scope="col">LEFT LEG</td>
				<td scope="col">RIGHT LEG</td>
				<td scope="col">SHILED (NOT WORKING)</td>
			</tr>
			-->
			</thead>
			<tbody>
			{% for record in ranking %}
			<tr class="table-dark">
				<th scope="row">{{ record.csx_rank }}</th>
				<td>
					<span class="flag-icon flag-icon-{{record.country}}"></span>
				</td>
				<td>
					<a href="{{record.steam_data.profileurl}}" target="_blank" ><img src="{{record.steam_data.avatar}}"></a>
				</td>
				<td>
					<form method="post" name="user_rank" action="user_detail.php">
						<input type="hidden" name="auth_id" value="{{ record.auth_id }}" />
						{% if record.name|trim matches '#^(\[[A-Z][A-Z]\])?.*(Player)$#' or record.name|trim matches '#^(\(\d\))?Player$#'%}
							<a href="#" onclick="javascript:user_rank[{{ loop.index0 }}].submit()">{{ record.steam_data.personaname }}</a>
						{% else %}
							<a href="#" onclick="javascript:user_rank[{{ loop.index0 }}].submit()">{{ record.name }}</a>
						{% endif %}
					</form>
				</td>
				<td>{{ record.online_time }}</td>
				<td>{{ record.csx_score }}</td>
				<td>{{ record.csx_kills }}</td>
				<td>{{ record.csx_deaths }}</td>
				<td>{{ record.csx_tks }}</td>
				<td><img src="images/{{ record.csx_elo }}" style="width:25%" alt="{{record.csx_elo_name}}"></td>
				<!--
				<td>{{ record.csx_hits }}</td>
				<td>{{ record.csx_dmg }}</td>
				<td>{{ record.csx_shots }}</td>
				<td>{{ record.csx_hs }}</td>
				<td>{{ record.efficiency }}</td>
				<td>{{ record.accuracy }}</td>
				<td>{{ record.accuracyHS }}</td>
				<td>{{ record.kdrate }}</td>
				<td>{{ record.h_head }}</td>
				<td>{{ record.h_chest }}</td>
				<td>{{ record.h_stomach }}</td>
				<td>{{ record.h_larm }}</td>
				<td>{{ record.h_rarm }}</td>
				<td>{{ record.h_lleg }}</td>
				<td>{{ record.h_rleg }}</td>
				<td>{{ record.h_shield }}</td>-->
			</tr>
			{% endfor %}
			</tbody>
		</table>
{% endblock %}
