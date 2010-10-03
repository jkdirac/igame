<?xml version="1.0" encoding="UTF-8"?>
<!-- this is a file generated by parser, please not modify -->
<!-- author: jkdirac, mail: jiangkun1@gamil.com -->
<MoDeL>
	<reaction id="amp_E_coli" name="amplification of E_coli" reversible="false" fast="false">
		<interface>
			<url>http://2010.igem.org/Team:USTC_Software</url>
			<short_desc>binding of IPTG and lacI153_tetramer</short_desc>
		</interface>
		<listOfCompartments>
			<compartment>
				<compartmentReference>Flask</compartmentReference>
				<currentCompartmentLabel>Flask</currentCompartmentLabel>
				<parentCompartmentLabel>ROOT</parentCompartmentLabel>
			</compartment>
			<compartment>
				<compartmentReference>E_coli</compartmentReference>
				<currentCompartmentLabel>E_coli</currentCompartmentLabel>
				<parentCompartmentLabel>Flask</parentCompartmentLabel>
			</compartment>
		</listOfCompartments>
		<listOfReactants>
		</listOfReactants>
		<listOfModifiers>
			<modifier>
				<speciesReference>E_coli_cell</speciesReference>
				<speciesLabel>E_coli_cell_0</speciesLabel>
				<compartmentLabel>E_coli</compartmentLabel>
			</modifier>
		</listOfModifiers>
		<listOfProducts>
			<product>
				<speciesReference>E_coli_cell</speciesReference>
				<speciesLabel>E_coli_cell_1</speciesLabel>
				<compartmentLabel>E_coli</compartmentLabel>
			</product>
		</listOfProducts>
		<listOfSubstituentTransfers>
		</listOfSubstituentTransfers>
		<kineticLaw>
			<forwardKineticlaw>
				<math>
					<apply>
						<times>
						</times>
						<ci>kon</ci>
						<ci>E_coli_cell_0</ci>
						<ci>lacI153_tetramer</ci>
						<ci>Flask</ci>
					</apply>
				</math>
				<listOfLocalParameters>
					<localParameter>
						<id>kon</id>
						<name>rate of binding</name>
						<value>2000000000</value>
						<units>litre_per_mole_per_second</units>
						<constant>true</constant>
					</localParameter>
				</listOfLocalParameters>
				<listOfReferencedParameters>
				</listOfReferencedParameters>
				<listOfConstraints>
				</listOfConstraints>
			</forwardKineticlaw>
			<reverseKineticLaw>
				<math>
					<times>
					</times>
					<ci>placI185lacI153_4</ci>
					<ci>koff</ci>
					<ci>E_coli</ci>
				</math>
				<listOfLocalparameters>
					<localParameter>
						<id>koff</id>
						<name>rate_of_unbinding</name>
						<value>0.2</value>
						<units>per_second</units>
						<constant>true</constant>
					</localParameter>
				</listOfLocalparameters>
				<listOfReferencedParameters>
				</listOfReferencedParameters>
				<listOfConstraints>
				</listOfConstraints>
			</reverseKineticLaw>
		</kineticLaw>
	</reaction>
</MoDeL>
